
#include "document.h"
#include <QFile>
#include <QDataStream>
#include <math.h>

Document::Document()
    : m_is_dirty(true)
    , m_is_filthy(true)
    , m_max_elements(16384)
    , m_elements(0)
    , m_building()
    , m_glass()
{
    m_element_ptr = new Element*[m_max_elements];
    m_building_index = new int[m_max_elements];
    m_glass_index = new int[m_max_elements];
}

Document::Document(const QString& file_name)
    : m_is_dirty(true)
    , m_is_filthy(true)
    , m_max_elements(16384)
    , m_elements(0)
    , m_building()
    , m_glass()
{
    QString error_message;
    m_element_ptr = new Element*[m_max_elements];
    m_building_index = new int[m_max_elements];
    m_glass_index = new int[m_max_elements];
    load(file_name, error_message);
}

Document::~Document()
{
    for (int i = 0; i < m_elements; i++) {
        delete m_element_ptr[i];
    }
    delete [] m_element_ptr;
    delete [] m_building_index;
    delete [] m_glass_index;
}

int Document::elements() const
{
    return m_elements;
}

int Document::facets() const
{
    int total = 0;
    for (int i = 0; i < m_elements; i++) {
        Element* e = m_element_ptr[i];
        if (!e->removed()) {
            total += e->model().facets();
        }
    }
    return total;
}

const Element* Document::element(int ix) const
{
    if (m_elements == 0)
        return NULL;
    int index = std::min(ix, m_elements -1);
    return m_element_ptr[index];
}

void Document::add_element(Element* e)
{
    if (e == NULL)
        return;
    if (m_elements >= m_max_elements) {
        double_the_storage();
    }
    m_element_ptr[m_elements] = e;
    m_building_index[m_elements] = m_building.vertex_count();
    m_glass_index[m_elements] = m_glass.vertex_count();
    if (m_elements == 0)
        m_is_filthy = true;

    m_building.add_element(e, false);
    m_glass.add_element(e, true);

    ++m_elements;
    m_is_dirty = true;
}

void Document::remove_element(int ix)
{
    if (m_elements == 0)
        return;
    int index = std::min(ix, m_elements - 1);
    m_element_ptr[index]->remove();
    m_building.update_element(m_building_index[index], m_element_ptr[index], false);
    m_glass.update_element(m_glass_index[index], m_element_ptr[index], true);
    m_is_dirty = true;
}

void Document::unremove_element(int ix)
{
    if (m_elements == 0)
        return;
    int index = std::min(ix, m_elements - 1);
    m_element_ptr[index]->unremove();
    m_building.update_element(m_building_index[index], m_element_ptr[index], false);
    m_glass.update_element(m_glass_index[index], m_element_ptr[index], true);
    m_is_dirty = true;
}

// This adds to document, only used with new document so far
bool Document::load(const QString& file_name, QString& error_message)
{
    TokenInterface ti(file_name);
    ti.advance();
    if (!expect(ti, "Bricks", error_message))
        return false;
    if (!expect(ti, "Document", error_message))
        return false;
    if (!expect(ti, "v0", error_message))
        return false;
    if (!expect(ti, ".", error_message))
        return false;
    if (!expect(ti, "1", error_message))
        return false;
    if (!expect(ti, ".", error_message))
        return false;
    if (!expect(ti, "0", error_message))
        return false;
    while (!ti.is_eof()) {
        QString ename = ti.current();
        ti.advance();
        if (ename == "HalfBrick") {
            float x, y, z;
            if (!expect(ti, "(", error_message))
                return false;
            if (!parse_float3(ti, x, y, z, error_message))
                return false;
            if (!expect(ti, ")", error_message))
                return false;
            add_element(new HalfBrickElement(x, y, z));
        } else if (ename == "Brick") {
            float x, y, z;
            int o;
            if (!expect(ti, "(", error_message))
                return false;
            if (!parse_float3(ti, x, y, z, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, o, error_message))
                return false;
            if (!expect(ti, ")", error_message))
                return false;
            add_element(new BrickElement(x, y, z, o));
        } else if (ename == "GableBrick") {
            float x, y, z;
            int o;
            if (!expect(ti, "(", error_message))
                return false;
            if (!parse_float3(ti, x, y, z, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, o, error_message))
                return false;
            if (!expect(ti, ")", error_message))
                return false;
            add_element(new GableBrickElement(x, y, z, o));
        } else if (ename == "Door") {
            float x, y, z;
            int o, w, h, hg, vg;
            if (!expect(ti, "(", error_message))
                return false;
            if (!parse_float3(ti, x, y, z, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, o, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, w, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, h, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, hg, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, vg, error_message))
                return false;
            if (!expect(ti, ")", error_message))
                return false;
            add_element(new DoorElement(x, y, z, o, w, h, hg, vg));
        } else if (ename == "Window") {
            float x, y, z;
            int o, w, h, hg, vg;
            if (!expect(ti, "(", error_message))
                return false;
            if (!parse_float3(ti, x, y, z, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, o, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, w, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, h, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, hg, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, vg, error_message))
                return false;
            if (!expect(ti, ")", error_message))
                return false;
            add_element(new WindowElement(x, y, z, o, w, h, hg, vg));
        } else if (ename == "Roof") {
            float x, y, z;
            int o, w;
            if (!expect(ti, "(", error_message))
                return false;
            if (!parse_float3(ti, x, y, z, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, o, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, w, error_message))
                return false;
            if (!expect(ti, ")", error_message))
                return false;
            add_element(new RoofElement(x, y, z, o, w));
        } else if (ename == "Ledge") {
            float x, y, z;
            int o, w;
            if (!expect(ti, "(", error_message))
                return false;
            if (!parse_float3(ti, x, y, z, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, o, error_message))
                return false;
            if (!expect(ti, ",", error_message))
                return false;
            if (!parse_integer(ti, w, error_message))
                return false;
            if (!expect(ti, ")", error_message))
                return false;
            add_element(new LedgeElement(x, y, z, o, w));
        } else {
            error_message = QString("Expecing 'HalfBrick' or 'Brick' 'GableBrick' or 'Window' or 'Door' or 'Roof' or 'Ledge' but found '%1'").arg(ename);
            return false;
        }
    }
    return true;
}

bool Document::save(const QString& file_name, QString& error_message) const
{
    QFile ffi(file_name);
    if (!ffi.open(QIODevice::WriteOnly)) {
        error_message = QString("Error opening file '%1'").arg(file_name);
        return false;
    }
    QDataStream ds(&ffi);
    QString msg = "Bricks Document v0.1.0\n";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    for (int i = 0; i < m_elements; i++) {
        if (!m_element_ptr[i]->removed()) {
            m_element_ptr[i]->save_to_file(ds);
        }
    }
    ffi.close();
    return true;
}

void Document::double_the_storage()
{
    // this will double the value of m_max_items
    // and copy existing data to new array
    // to seamlessly keep the buffer larger than data
    m_max_elements = 2 * m_max_elements;
    Element** temp_element_ptr = new Element*[m_max_elements];
    int* temp_building_index = new int[m_max_elements];
    int* temp_glass_index = new int[m_max_elements];

    for (int i = 0; i < m_elements; i++) {
        temp_element_ptr[i] = m_element_ptr[i];
        temp_building_index[i] = m_building_index[i];
        temp_glass_index[i] = m_glass_index[i];
    }
    delete [] m_element_ptr;
    delete [] m_building_index;
    delete [] m_glass_index;
    m_element_ptr = temp_element_ptr;
    m_building_index = temp_building_index;
    m_glass_index = temp_glass_index;
}

bool Document::expect(TokenInterface& ti, const QString& pattern, QString& error_message)
{
    if (ti.current() == pattern) {
        ti.advance();
        return true;
    }
    error_message = QString("Expecing '%1' but found '%2'").arg(pattern).arg(ti.current());
    return false;
}

bool Document::parse_float3(TokenInterface& ti, float& x, float& y, float& z, QString& error_message)
{
    if (!parse_float(ti, x, error_message))
        return false;
    if (!expect(ti, ",", error_message))
        return false;
    if (!parse_float(ti, y, error_message))
        return false;
    if (!expect(ti, ",", error_message))
        return false;
    return parse_float(ti, z, error_message);
}

bool Document::parse_integer(TokenInterface& ti, int &v, QString& error_message)
{
    QString s = "";
    if (ti.current() == "+" || ti.current() == "-") {
        s += ti.current();
        ti.advance();
    }
    if (!ti.is_unsigned_integer()) {
        error_message = QString("expecting integer but found '%1'").arg(ti.current());
        return false;
    }
    s += ti.current();
    ti.advance();
    bool res;
    v = s.toInt(&res);
    if (!res) {
        error_message = QString("error converting integer '%1'").arg(s);
        return false;
    }
    return true;
}

bool Document::parse_float(TokenInterface& ti, float& v, QString& error_message)
{
    QString s = "";
    if (ti.current() == "+" || ti.current() == "-") {
        s += ti.current();
        ti.advance();
    }
    if (!ti.is_unsigned_integer()) {
        error_message = QString("expecting float but found '%1'").arg(ti.current());
        return false;
    }
    s += ti.current();
    ti.advance();
    if (ti.current() == ".") {
        s += ".";
        ti.advance();
        if (!ti.is_unsigned_integer()) {
            error_message = QString("expecting float but found '%1'").arg(ti.current());
            return false;
        }
        s += ti.current();
        ti.advance();
    }
    bool res;
    v = s.toFloat(&res);
    if (!res) {
        error_message = QString("error converting float '%1'").arg(s);
        return false;
    }
    return true;
}

bool Document::is_dirty() const
{
    return m_is_dirty || m_is_filthy;
}

bool Document::is_filthy() const
{
    return m_is_filthy;
}

void Document::make_clean()
{
    m_is_dirty = false;
    m_is_filthy = false;
}

void Document::make_dirty()
{
    m_is_dirty = true;
}

void Document::make_filthy()
{
    m_is_filthy = true;
}

bool Document::contains(Float3 pos) const
{
    if (m_elements < 1)
        return false;
    for (int i = 0; i < m_elements; i++) {
        if (!m_element_ptr[i]->removed()) {
            if (m_element_ptr[i]->contains(pos))
                return true;
        }
    }
    return false;
}

BoundingBox Document::combine_bounding_boxes(BoundingBox bb1, BoundingBox bb2) const
{
    BoundingBox bb;
    bb.vmin.v1 = fmin(bb1.vmin.v1, bb2.vmin.v1);
    bb.vmin.v2 = fmin(bb1.vmin.v2, bb2.vmin.v2);
    bb.vmin.v3 = fmin(bb1.vmin.v3, bb2.vmin.v3);
    bb.vmax.v1 = fmax(bb1.vmax.v1, bb2.vmax.v1);
    bb.vmax.v2 = fmax(bb1.vmax.v2, bb2.vmax.v2);
    bb.vmax.v3 = fmax(bb1.vmax.v3, bb2.vmax.v3);
    return bb;
}

BoundingBox Document::bounding_box(bool roof_filter) const
{
    float dx = Element::dimx / 2.0;
    BoundingBox bb = {-dx, 0.0, -dx, dx, Element::dimh, dx};
    if (m_elements <= 0)
        return bb;
    bool first = true;
    for (int i = 0; i < m_elements; i++) {
        Element* e = m_element_ptr[i];
        if (e != NULL ) {
            if (!e->removed()) {
                if (first) {
                    bb = e->bounding_box();
                    first = false;
                } else {
                    bb = combine_bounding_boxes(bb, e->bounding_box());
                }
                if (roof_filter) {
                    filter_roof(bb.vmin.v1);
                    filter_roof(bb.vmin.v3);
                    filter_roof(bb.vmax.v1);
                    filter_roof(bb.vmax.v3);
                }
            }
        }
    }
    return bb;
}

void Document::filter_roof(float& v) const
{
    v = round(v + 0.5) - 0.5;
}

const VertexImage& Document::building() const
{
    return m_building;
}

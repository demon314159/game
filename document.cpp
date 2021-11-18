
#include "document.h"
#include <QFile>
#include <QDataStream>

Document::Document()
    : m_is_dirty(false)
    , m_max_elements(16384)
    , m_elements(0)
    , m_dummy(HalfBrickElement(0.0, 0.0, 0.0))
{
    m_element_ptr = new Element*[m_max_elements];
}

Document::Document(const QString& file_name)
    : m_is_dirty(false)
    , m_max_elements(16384)
    , m_elements(0)
    , m_dummy(HalfBrickElement(0.0, 0.0, 0.0))
{
    QString error_message;
    m_element_ptr = new Element*[m_max_elements];
    load(file_name, error_message);
}

Document::~Document()
{
    for (int i = 0; i < m_elements; i++) {
        delete m_element_ptr[i];
    }
    delete [] m_element_ptr;
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
        total += e->model().facets();
    }
    return total;
}

const Element* Document::element(int ix) const
{
    if (m_elements == 0) { // Return this instead of null pointer
        return &m_dummy;
    }
    int index = std::min(ix, m_elements -1);
    return m_element_ptr[index];
}

void Document::add_element(Element* e)
{
    if (m_elements >= m_max_elements) {
        double_the_storage();
    }
    m_element_ptr[m_elements] = e;
    ++m_elements;
    m_is_dirty = true;
}

void Document::add_element(Element* e, int ix)
{
    if (m_elements >= m_max_elements) {
        double_the_storage();
    }
    int index = std::min(ix, m_elements);
    for (int i = index; i < m_elements; i++) {
        m_element_ptr[m_elements - i + index] = m_element_ptr[m_elements - i + index - 1];
    }
    m_element_ptr[index] = e;
    ++m_elements;
    m_is_dirty = true;
}

Element* Document::remove_element(int ix)
{
    if (m_elements == 0) { // Return this instead of null pointer
        return &m_dummy;
    }
    int index = std::min(ix, m_elements - 1);
    Element* e = m_element_ptr[index];
    printf("e = %p\n", e);
    --m_elements;
    for (int i = index; i < m_elements; i++) {
        m_element_ptr[i] = m_element_ptr[i + 1];
    }
    m_is_dirty = true;
    return e;
}

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
            error_message = QString("Expecing 'HalfBrick' or 'Brick' or 'Window' or 'Ledge' but found '%1'").arg(ename);
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
        m_element_ptr[i]->save_to_file(ds);
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
    Element** temp = new Element*[m_max_elements];
    for (int i = 0; i < m_elements; i++) {
        temp[i] = m_element_ptr[i];
    }
    delete [] m_element_ptr;
    m_element_ptr = temp;
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
    return m_is_dirty;
}

void Document::make_clean()
{
    m_is_dirty = false;
}

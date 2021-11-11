
#include "document.h"
#include <QFile>
#include <QDataStream>
#include <stdio.h>

#define VERBOSE

Document::Document()
    : m_model_obsolete(true)
    , m_max_elements(16384)
    , m_elements(0)
    , m_error_flag(false)
    , m_error_message("no errors")
{
    m_element_ptr = new Element*[m_max_elements];
}

Document::~Document()
{
    for (int i = 0; i < m_elements; i++) {
        delete m_element_ptr[i];
    }
    delete [] m_element_ptr;
}

bool Document::model_obsolete() const
{
    return m_model_obsolete;
}

int Document::elements() const
{
    return m_elements;
}

bool Document::error_flag() const
{
    return m_error_flag;
}

QString Document::error_message() const
{
    return m_error_message;
}

void Document::add_element(Element* e, int ix)
{
    if (m_elements >= m_max_elements) {
        double_the_storage();
    }
    for (int i = ix; i < m_elements; i++) {
        m_element_ptr[m_elements - i + ix] = m_element_ptr[m_elements - i + ix - 1];
    }
    m_element_ptr[ix] = e;
    m_model_obsolete = true;
}

void Document::add_element(Element* e)
{
    if (m_elements >= m_max_elements) {
        double_the_storage();
    }
    m_element_ptr[m_elements] = e;
    ++m_elements;
    m_model_obsolete = true;
}

Element* Document::remove_element(int ix)
{
    Element* e = m_element_ptr[ix];
    --m_elements;
    for (int i = ix; i < m_elements; i++) {
        m_element_ptr[ix] = m_element_ptr[ix + 1];
    }
    m_model_obsolete = true;
    return e;
}

Element* Document::get_element(int i) const
{
    return m_element_ptr[i];
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

void Document::save(QString& file_name) const
{
    QFile ffi(file_name);
    if (!ffi.open(QIODevice::WriteOnly)) {
#ifdef VERBOSE
        printf("<<< Error opening file '%s' >>>\n", file_name.toLatin1().data());
#endif
        return;
    }

    QDataStream ds(&ffi);
    QString msg = "Bricks Document v0.1.0\n";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    for (int i = 0; i < m_elements; i++) {
        m_element_ptr[i]->save_to_file(ds);
    }
    ffi.close();
}

bool Document::load(QString& file_name)
{
    TokenInterface ti(file_name);
    ti.advance();
    if (!expect(ti, "Bricks"))
        return false;
    if (!expect(ti, "Document"))
        return false;
    if (!expect(ti, "v0"))
        return false;
    if (!expect(ti, "."))
        return false;
    if (!expect(ti, "1"))
        return false;
    if (!expect(ti, "."))
        return false;
    if (!expect(ti, "0"))
        return false;
    while (!ti.is_eof()) {
        QString ename = ti.current();
        ti.advance();
        if (ename == "HalfBrick") {
            float x, y, z;
            if (!expect(ti, "("))
                return false;
            if (!parse_float3(ti, x, y, z))
                return false;
            if (!expect(ti, ")"))
                return false;
            add_element(new HalfBrickElement(x, y, z));
        } else if (ename == "Brick") {
            float x, y, z;
            int o;
            if (!expect(ti, "("))
                return false;
            if (!parse_float3(ti, x, y, z))
                return false;
            if (!expect(ti, ","))
                return false;
            if (!parse_integer(ti, o))
                return false;
            if (!expect(ti, ")"))
                return false;
            add_element(new BrickElement(x, y, z, o));
        } else if (ename == "Window") {
            float x, y, z;
            int o, w, h, hg, vg;
            if (!expect(ti, "("))
                return false;
            if (!parse_float3(ti, x, y, z))
                return false;
            if (!expect(ti, ","))
                return false;
            if (!parse_integer(ti, o))
                return false;
            if (!expect(ti, ","))
                return false;
            if (!parse_integer(ti, w))
                return false;
            if (!expect(ti, ","))
                return false;
            if (!parse_integer(ti, h))
                return false;
            if (!expect(ti, ","))
                return false;
            if (!parse_integer(ti, hg))
                return false;
            if (!expect(ti, ","))
                return false;
            if (!parse_integer(ti, vg))
                return false;
            if (!expect(ti, ")"))
                return false;
            add_element(new WindowElement(x, y, z, o, w, h, hg, vg));
        } else if (ename == "Ledge") {
            float x, y, z;
            int o, w;
            if (!expect(ti, "("))
                return false;
            if (!parse_float3(ti, x, y, z))
                return false;
            if (!expect(ti, ","))
                return false;
            if (!parse_integer(ti, o))
                return false;
            if (!expect(ti, ","))
                return false;
            if (!parse_integer(ti, w))
                return false;
            if (!expect(ti, ")"))
                return false;
            add_element(new LedgeElement(x, y, z, o, w));
        } else {
            m_error_message = QString("Expecing 'HalfBrick' or 'Brick' or 'Window' or 'Ledge' but found '%1'").arg(ename);
            m_error_flag = true;
            return false;
        }
    }
    return true;
}

bool Document::expect(TokenInterface& ti, const QString& pattern)
{
    if (ti.current() == pattern) {
        ti.advance();
        return true;
    }
    m_error_message = QString("Expecing '%1' but found '%2'").arg(pattern).arg(ti.current());
    m_error_flag = true;
    return false;
}

bool Document::parse_float3(TokenInterface& ti, float& x, float& y, float& z)
{
    if (!parse_float(ti, x))
        return false;
    if (!expect(ti, ","))
        return false;
    if (!parse_float(ti, y))
        return false;
    if (!expect(ti, ","))
        return false;
    return parse_float(ti, z);
}

bool Document::parse_integer(TokenInterface& ti, int &v)
{
    QString s = "";
    if (ti.current() == "+" || ti.current() == "-") {
        s += ti.current();
        ti.advance();
    }
    if (!ti.is_unsigned_integer()) {
        m_error_message = QString("expecting integer but found '%1'").arg(ti.current());
        return false;
    }
    s += ti.current();
    ti.advance();
    bool res;
    v = s.toInt(&res);
    if (!res) {
        m_error_message = QString("error converting integer '%1'").arg(s);
        return false;
    }
    return true;
}

bool Document::parse_float(TokenInterface& ti, float& v)
{
    QString s = "";
    if (ti.current() == "+" || ti.current() == "-") {
        s += ti.current();
        ti.advance();
    }
    if (!ti.is_unsigned_integer()) {
        m_error_message = QString("expecting float but found '%1'").arg(ti.current());
        return false;
    }
    s += ti.current();
    ti.advance();
    if (ti.current() == ".") {
        s += ".";
        ti.advance();
        if (!ti.is_unsigned_integer()) {
            m_error_message = QString("expecting float but found '%1'").arg(ti.current());
            return false;
        }
        s += ti.current();
        ti.advance();
    }
    bool res;
    v = s.toFloat(&res);
    if (!res) {
        m_error_message = QString("error converting float '%1'").arg(s);
        return false;
    }
    return true;
}

void Document::build_model(CadModel* model)
{
    for (int i = 0; i < m_elements; i++) {
        Element* e = m_element_ptr[i];
        float3 pos = e->get_pos();
        CadModel cm(e->model());
        model->add(cm, pos.v1, pos.v2 * Element::dimh, pos.v3);
    }
    m_model_obsolete = false;
}

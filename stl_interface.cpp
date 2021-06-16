
#include "stl_interface.h"

#define VERBOSE

StlInterface::StlInterface(const QString& file_name)
    : m_file_is_valid(false)
    , m_bi(file_name)
    , m_error_message("no errors")
    , m_ambient_color({0.329412, 0.517647, 1.000000})
    , m_diffuse_color({0.329412, 0.517647, 1.000000})
    , m_emissive_color({0.0, 0.0, 0.0})
    , m_specular_color({0.164706, 0.258824, 0.500000})
    , m_shininess(0.400000)
    , m_transparency(0.0)
    , m_facet_count(0)
    , m_v1(NULL)
    , m_v2(NULL)
    , m_v3(NULL)
{
#ifdef VERBOSE
    printf("StlInterface(%s)\n", file_name.toLatin1().data());
#endif
    parse();
#ifdef VERBOSE
    printf("%d facets\n", m_facet_count);
#endif
}

StlInterface::~StlInterface()
{
#ifdef VERBOSE
    printf("~StlInterface()\n");
#endif
    if (m_v1 != NULL)
        delete [] m_v1;
    if (m_v2 != NULL)
        delete [] m_v2;
    if (m_v3 != NULL)
        delete [] m_v3;
}

float3 StlInterface::ambient_color() const
{
    return m_ambient_color;
}

float3 StlInterface::diffuse_color() const
{
    return m_diffuse_color;
}

float3 StlInterface::emissive_color() const
{
    return m_emissive_color;
}

float3 StlInterface::specular_color() const
{
    return m_specular_color;
}

float StlInterface::shininess() const
{
    return m_shininess;
}

float StlInterface::transparency() const
{
    return m_transparency;
}

int StlInterface::facets() const
{
    return m_facet_count;
}

float3 StlInterface::facet_v1(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v1[facet_ix];
    } else {
        float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

float3 StlInterface::facet_v2(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v2[facet_ix];
    } else {
        float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

float3 StlInterface::facet_v3(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v3[facet_ix];
    } else {
        float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

bool StlInterface::file_is_valid() const
{
    return m_file_is_valid;
}

QString StlInterface::error_message() const
{
    return m_error_message;
}

bool StlInterface::parse()
{
    m_file_is_valid = false;
    int header_count = 80;
    while (!m_bi.is_eof() && header_count > 0) {
        m_bi.advance();
        --header_count;
    }
    if (m_bi.is_eof()) {
        m_error_message = "File is too small";
        return false;
    }
    int n = m_bi.get_int();
    if (n < 1) {
        m_error_message = "No faces found";
        return false;
    }
    m_v1 = new float3[n];
    m_v2 = new float3[n];
    m_v3 = new float3[n];
    for (int i = 0; i < n; i++) {
        if (m_bi.is_eof()) {
            m_error_message = QString("End Of File at face %1 out of %2").arg(i+1).arg(n);
            return false;
        }
        m_bi.get_float();              // Skip normal vector
        m_bi.get_float();
        m_bi.get_float();
        m_v1[i].v1 = m_bi.get_float(); // Get first vertex
        m_v1[i].v2 = m_bi.get_float();
        m_v1[i].v3 = m_bi.get_float();
        m_v2[i].v1 = m_bi.get_float(); // Get second vertex
        m_v2[i].v2 = m_bi.get_float();
        m_v2[i].v3 = m_bi.get_float();
        m_v3[i].v1 = m_bi.get_float(); // Get third vertex
        m_v3[i].v2 = m_bi.get_float();
        m_v3[i].v3 = m_bi.get_float();
        if (m_bi.is_eof()) {
            m_error_message = QString("End Of File at face %1 out of %2").arg(i+1).arg(n);
            return false;
        }
        m_bi.get_unsigned_short();     // Skip attribute
    }
    m_facet_count = n;
    m_file_is_valid = true;
    return m_file_is_valid;
}


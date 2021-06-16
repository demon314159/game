
#include "stl_interface.h"

#define notVERBOSE

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
}

StlInterface::~StlInterface()
{
#ifdef VERBOSE
    printf("~VrmlInterface()\n");
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

bool StlInterface::parse()
{
    m_file_is_valid = false;
    return m_file_is_valid;
}

bool StlInterface::file_is_valid() const
{
    return m_file_is_valid;
}

QString StlInterface::error_message() const
{
    return m_error_message;
}


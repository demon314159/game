
#include "vrml_interface.h"

#define notVERBOSE

VrmlInterface::VrmlInterface(const QString& file_name)
    : m_file_is_valid(false)
    , m_pass2(false)
    , m_ti(file_name)
    , m_error_message("no errors")
    , m_per_face_indexed(false)
    , m_ambient_color_count(0)
    , m_ambient_color(NULL)
    , m_diffuse_color_count(0)
    , m_diffuse_color(NULL)
    , m_emissive_color_count(0)
    , m_emissive_color(NULL)
    , m_specular_color_count(0)
    , m_specular_color(NULL)
    , m_shininess_count(0)
    , m_shininess(NULL)
    , m_transparency_count(0)
    , m_transparency(NULL)
    , m_point_count(0)
    , m_point(NULL)
    , m_coord_index_count(0)
    , m_coord_index(NULL)
    , m_material_index_count(0)
    , m_material_index(NULL)
{
#ifdef VERBOSE
    printf("VrmlInterface(%s)\n", file_name.toLatin1().data());
#endif
    parse();
}

VrmlInterface::~VrmlInterface()
{
#ifdef VERBOSE
    printf("~VrmlInterface()\n");
#endif
    if (m_ambient_color != NULL)
        delete [] m_ambient_color;
    if (m_diffuse_color != NULL)
        delete [] m_diffuse_color;
    if (m_emissive_color != NULL)
        delete [] m_emissive_color;
    if (m_specular_color != NULL)
        delete [] m_specular_color;
    if (m_shininess != NULL)
        delete [] m_shininess;
    if (m_transparency != NULL)
        delete [] m_transparency;
    if (m_point != NULL)
        delete [] m_point;
    if (m_coord_index != NULL)
        delete [] m_coord_index;
    if (m_material_index != NULL)
        delete [] m_material_index;
}

int VrmlInterface::materials() const
{
    return m_ambient_color_count;
}

int VrmlInterface::points() const
{
    return m_point_count;
}

int VrmlInterface::facets() const
{
    return m_coord_index_count;
}

Float3 VrmlInterface::ambient_color(int material_ix) const
{
    return m_ambient_color[material_ix];
}

Float3 VrmlInterface::diffuse_color(int material_ix) const
{
    return m_diffuse_color[material_ix];
}

Float3 VrmlInterface::emissive_color(int material_ix) const
{
    return m_emissive_color[material_ix];
}

Float3 VrmlInterface::specular_color(int material_ix) const
{
    return m_specular_color[material_ix];
}

float VrmlInterface::shininess(int material_ix) const
{
    return m_shininess[material_ix];
}

float VrmlInterface::transparency(int material_ix) const
{
    return m_transparency[material_ix];
}

Float3 VrmlInterface::point(int point_ix) const
{
    return m_point[point_ix];
}

Int3 VrmlInterface::facet_points(int facet_ix) const
{
    return m_coord_index[facet_ix];
}

int VrmlInterface::facet_material(int facet_ix) const
{
    if (m_per_face_indexed)
        return m_material_index[facet_ix];
    else
        return 0;
}

bool VrmlInterface::parse()
{
    m_file_is_valid = false;
    m_pass2 = false;

#ifdef VERBOSE
    printf("Pass 1\n");
#endif
    if (!parse_one_pass())
        return false;
    if (!sanity_check())
        return false;
#ifdef VERBOSE
    printf("per_face_indexed = %s\n", m_per_face_indexed ? "true" : "false");
    printf("ambient_color_count = %d\n", m_ambient_color_count);
    printf("diffuse_color_count = %d\n", m_diffuse_color_count);
    printf("emissive_color_count = %d\n", m_emissive_color_count);
    printf("specular_color_count = %d\n", m_specular_color_count);
    printf("shininess_count = %d\n", m_shininess_count);
    printf("transparency_count = %d\n", m_transparency_count);
    printf("point_count = %d\n", m_point_count);
    printf("coord_index_count = %d\n", m_coord_index_count);
    printf("material_index_count = %d\n", m_material_index_count);
#endif
    m_ambient_color = new Float3[m_ambient_color_count];
    m_diffuse_color = new Float3[m_diffuse_color_count];
    m_emissive_color = new Float3[m_emissive_color_count];
    m_specular_color = new Float3[m_specular_color_count];
    m_shininess = new float[m_shininess_count];
    m_transparency = new float[m_transparency_count];
    m_point = new Float3[m_point_count];
    m_coord_index = new Int3[m_coord_index_count];
    if (m_per_face_indexed) {
        m_material_index = new int[m_material_index_count];
    }
    m_pass2 = true;
#ifdef VERBOSE
    printf("Pass 2\n");
#endif
    m_file_is_valid = parse_one_pass();
    return m_file_is_valid;
}

bool VrmlInterface::parse_one_pass()
{
    m_ti.rewind();
    m_ti.advance();
    if (!expect("Separator"))
        return false;
    if (!expect("{"))
        return false;
    while (m_ti.current() != "}") {
        if (!parse_block())
            return false;
    }
    return expect("}");
}

bool VrmlInterface::file_is_valid() const
{
    return m_file_is_valid;
}

QString VrmlInterface::error_message() const
{
    return m_error_message;
}

bool VrmlInterface::sanity_check()
{
    if (m_ambient_color_count < 1) {
        m_error_message = "ambient color table is empty";
        return false;
    }
    if (m_diffuse_color_count != m_ambient_color_count) {
        m_error_message = "diffuse color table is wrong size";
        return false;
    }
    if (m_emissive_color_count != m_ambient_color_count) {
        m_error_message = "emissive color table is wrong size";
        return false;
    }
    if (m_specular_color_count != m_ambient_color_count) {
        m_error_message = "specular color table is wrong size";
        return false;
    }
    if (m_shininess_count != m_ambient_color_count) {
        m_error_message = "shininess table is wrong size";
        return false;
    }
    if (m_transparency_count != m_ambient_color_count) {
        m_error_message = "transparency table is wrong size";
        return false;
    }
    if (m_point_count < 3) {
        m_error_message = "not enough points";
        return false;
    }
    if (m_coord_index_count < 3) {
        m_error_message = "not coord indexes";
        return false;
    }
    if (m_per_face_indexed) {
        if (m_material_index_count != m_coord_index_count) {
            m_error_message = "material index table is wrong size";
            return false;
        }
    }
    return true;
}

bool VrmlInterface::parse_block()
{
    if (m_ti.current() == "MaterialBinding") {
        return parse_material_binding();
    } else if (m_ti.current() == "Material") {
        return parse_material();
    } else if (m_ti.current() == "Coordinate3") {
        bool res = parse_coordinate3();
        return res;
    } else if (m_ti.current() == "IndexedFaceSet") {
        return parse_indexed_face_set();
    } else {
        m_error_message = QString("unknown identifier: '%1'").arg(m_ti.current());
        return false;
    }
}

bool VrmlInterface::parse_material_binding()
{
    m_ti.advance();
    if (!expect("{"))
        return false;
    if (!expect("value"))
        return false;
    if (m_ti.current() == "PER_FACE_INDEXED") {
        m_ti.advance();
        m_per_face_indexed = true;
    } else if (m_ti.current() == "OVERALL") {
        m_ti.advance();
        m_per_face_indexed = false;
    } else {
        m_error_message = QString("unknown identifier: '%1'").arg(m_ti.current());
        return false;
    }
    return expect("}");
}

bool VrmlInterface::parse_material()
{
    m_ti.advance();
    if (!expect("{"))
        return false;
    while (m_ti.current() != "}") {
        if (!parse_material_block())
            return false;
    }
    return expect("}");
}

bool VrmlInterface::parse_material_block()
{
    if (m_ti.current() == "ambientColor") {
        return parse_float3_array(m_ambient_color_count, m_ambient_color);
    } else if (m_ti.current() == "diffuseColor") {
        return parse_float3_array(m_diffuse_color_count, m_diffuse_color);
    } else if (m_ti.current() == "emissiveColor") {
        return parse_float3_array(m_emissive_color_count, m_emissive_color);
    } else if (m_ti.current() == "specularColor") {
        return parse_float3_array(m_specular_color_count, m_specular_color);
    } else if (m_ti.current() == "shininess") {
        return parse_float_array(m_shininess_count, m_shininess);
    } else if (m_ti.current() == "transparency") {
        return parse_float_array(m_transparency_count, m_transparency);
    } else {
        m_error_message = QString("unknown identifier: '%1'").arg(m_ti.current());
        return false;
    }
}

bool VrmlInterface::parse_coordinate3()
{
    m_ti.advance();
    if (!expect("{"))
        return false;
    if (m_ti.current() == "point") {
        if (!parse_float3_array(m_point_count, m_point))
            return false;
    } else {
        m_error_message = QString("unknown identifier: '%1'").arg(m_ti.current());
        return false;
    }
    return expect("}");
}

bool VrmlInterface::parse_indexed_face_set()
{
    m_ti.advance();
    if (!expect("{"))
        return false;
    while (m_ti.current() != "}") {
        if (!parse_indexed_face_set_block())
            return false;
    }
    return expect("}");
}

bool VrmlInterface::parse_indexed_face_set_block()
{
    if (m_ti.current() == "coordIndex") {
        return parse_integer3_array(m_coord_index_count, m_coord_index);
    } else if (m_ti.current() == "materialIndex") {
        return parse_integer_array(m_material_index_count, m_material_index);
    } else {
        m_error_message = QString("unknown identifier: '%1'").arg(m_ti.current());
        return false;
    }
}

bool VrmlInterface::expect(const QString& pattern)
{
    if (m_ti.current() == pattern) {
        m_ti.advance();
        return true;
    }
    m_error_message = QString("Expecing '%1' but found '%2'").arg(pattern).arg(m_ti.current());
    return false;
}

bool VrmlInterface::parse_float_array(int& count, float* ptr)
{
    float v;
    m_ti.advance();
    if (!expect("["))
        return false;
    if (!parse_float(v))
        return false;
    if (m_pass2)
        *ptr++ = v;
    else
        ++count;
    while (m_ti.current() == ",") {
        m_ti.advance();
        if (m_ti.current() != "]") {
            if (!parse_float(v))
                return false;
            if (m_pass2)
                *ptr++ = v;
            else
              ++count;
        }
    }
    return expect("]");
}

bool VrmlInterface::parse_float3_array(int& count, Float3* ptr)
{
    Float3 v;

    m_ti.advance();
    if (!expect("["))
        return false;
    if (!parse_float3(v))
        return false;
    if (m_pass2)
        *ptr++ = v;
    else
        ++count;
    while (m_ti.current() == ",") {
        m_ti.advance();
        if (m_ti.current() != "]") {
            if (!parse_float3(v))
                return false;
            if (m_pass2)
                *ptr++ = v;
            else
                ++count;
        }
    }
    return expect("]");
}

bool VrmlInterface::parse_float(float& v)
{
    QString s = "";
    if (m_ti.current() == "+" || m_ti.current() == "-") {
        if (m_pass2)
            s += m_ti.current();
        m_ti.advance();
    }
    if (!m_ti.is_unsigned_integer()) {
        m_error_message = QString("expecting float but found '%1'").arg(m_ti.current());
        return false;
    }
    if (m_pass2)
        s += m_ti.current();
    m_ti.advance();
    if (m_ti.current() == ".") {
        if (m_pass2)
            s += ".";
        m_ti.advance();
        if (!m_ti.is_unsigned_integer()) {
            m_error_message = QString("expecting float but found '%1'").arg(m_ti.current());
            return false;
        }
        if (m_pass2)
            s += m_ti.current();
        m_ti.advance();
    }
    if (m_pass2) {
        bool res;
        v = s.toFloat(&res);
        if (!res) {
            m_error_message = QString("error converting float '%1'").arg(s);
            return false;
        }
    } else
        v = 0.0;
    return true;
}

bool VrmlInterface::parse_float3(Float3& v)
{
    if (!parse_float(v.v1))
        return false;
    if (!parse_float(v.v2))
        return false;
    return parse_float(v.v3);
}

bool VrmlInterface::parse_integer3_array(int& count, Int3* ptr)
{
    Int3 v;
    m_ti.advance();
    if (!expect("["))
        return false;
    if (!parse_integer3(v))
        return false;
    if (m_pass2)
        *ptr++ = v;
    else
        ++count;
    while (m_ti.current() == ',') {
        m_ti.advance();
        if (m_ti.current() != "]") {
            if (!parse_integer3(v))
                return false;
            if (m_pass2)
                *ptr++ = v;
            else
                ++count;
        }
    }
    return expect("]");
}

bool VrmlInterface::parse_integer_array(int& count, int* ptr)
{
    int v;

    m_ti.advance();
    if (!expect("["))
        return false;
    if (!parse_integer(v))
        return false;
    if (m_pass2)
        *ptr++ = v;
    else
        ++count;
    while (m_ti.current() == ",") {
        m_ti.advance();
        if (m_ti.current() != "]") {
            if (!parse_integer(v))
                return false;
            if (m_pass2)
                *ptr++ = v;
            else
                ++count;
        }
    }
    return expect("]");
}

bool VrmlInterface::parse_integer3(Int3& v)
{
    if (!parse_integer(v.v1))
        return false;
    if (!expect(","))
        return false;
    if (!parse_integer(v.v2))
        return false;
    if (!expect(","))
        return false;
    if (!parse_integer(v.v3))
        return false;
    if (!expect(","))
        return false;
    if (!expect("-"))
        return false;
    if (!expect("1"))
        return false;
    return true;
}

bool VrmlInterface::parse_integer(int &v)
{
    QString s = "";
    if (m_ti.current() == "+" || m_ti.current() == "-") {
        if (m_pass2)
            s += m_ti.current();
        m_ti.advance();
    }
    if (!m_ti.is_unsigned_integer()) {
        m_error_message = QString("expecting integer but found '%1'").arg(m_ti.current());
        return false;
    }
    if (m_pass2)
        s += m_ti.current();
    m_ti.advance();
    if (m_pass2) {
        bool res;
        v = s.toInt(&res);
        if (!res) {
            m_error_message = QString("error converting integer '%1'").arg(s);
            return false;
        }
    } else
        v = 0;
    return true;
}



#ifndef _VRML_INTERFACE_H_
#define _VRML_INTERFACE_H_

#include <QString>
#include "token_interface.h"
#include "float3.h"
#include "int3.h"

class VrmlInterface
{
public:
    VrmlInterface(const QString& file_name);
    ~VrmlInterface();
    bool file_is_valid() const;
    QString error_message() const;
    int materials() const;
    int points() const;
    int facets() const;
    float3 ambient_color(int material_ix) const;
    float3 diffuse_color(int material_ix) const;
    float3 emissive_color(int material_ix) const;
    float3 specular_color(int material_ix) const;
    float shininess(int material_ix) const;
    float transparency(int material_ix) const;
    float3 point(int point_ix) const;
    int3 facet_points(int facet_ix) const;
    int facet_material(int facet_ix) const;

private:
    bool m_file_is_valid;
    bool m_pass2;
    TokenInterface m_ti;
    QString m_error_message;
    bool m_per_face_indexed;
    int m_ambient_color_count;
    float3* m_ambient_color;
    int m_diffuse_color_count;
    float3* m_diffuse_color;
    int m_emissive_color_count;
    float3* m_emissive_color;
    int m_specular_color_count;
    float3* m_specular_color;
    int m_shininess_count;
    float* m_shininess;
    int m_transparency_count;
    float* m_transparency;
    int m_point_count;
    float3* m_point;
    int m_coord_index_count;
    int3* m_coord_index;
    int m_material_index_count;
    int* m_material_index;
    bool sanity_check();
    bool parse();
    bool parse_one_pass();
    bool parse_block();
    bool parse_material_binding();
    bool parse_material();
    bool parse_material_block();
    bool parse_coordinate3();
    bool parse_indexed_face_set();
    bool parse_indexed_face_set_block();
    bool expect(const QString& pattern);
    bool parse_float_array(int& count, float* ptr);
    bool parse_float3_array(int& count, float3* ptr);
    bool parse_float(float& v);
    bool parse_float3(float3& v);
    bool parse_integer3_array(int& count, int3* ptr);
    bool parse_integer_array(int& count, int* ptr);
    bool parse_integer3(int3& v);
    bool parse_integer(int& v);
};

#endif // _VRML_INTERFACE_H_

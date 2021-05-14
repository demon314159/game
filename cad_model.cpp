//
// cad_model.cpp
//
#include "cad_model.h"

CadModel::CadModel(const QString& file_name)
    : m_points(0)
    , m_coords(0)
{
    FILE* ffi = fopen(file_name.toLatin1().data(), "r");
    if (ffi == NULL) {
        printf("<<< Error opening file '%s' >>>\n", file_name.toLatin1().data());
    } else {
        printf("Open file '%s'\n", file_name.toLatin1().data());
        parse_file(ffi);
        fclose(ffi);
        printf("Close file '%s'\n", file_name.toLatin1().data());
        printf("m_points = %d\n", m_points);
        printf("m_coords = %d\n", m_coords);
    }
}

void CadModel::parse_file(FILE* ffi)
{
    char buf[512];
    char* ptr;
    bool point_flag = false;
    bool coord_flag = false;

    ptr = fgets(buf, 512, ffi);
    while (ptr != NULL) {
//        printf("%s", buf);
        if (point_flag) {
            if (buf[0] == ']') {
                point_flag = false;
            } else {
                parse_point_line(buf);
            }
        } else  if (coord_flag) {
            if (buf[0] == ']') {
                coord_flag = false;
            } else {
                parse_coord_line(buf);
            }
        } else {
            point_flag = (0 == strncmp(buf, "point [", 7)) ? true : false;
            coord_flag = (0 == strncmp(buf, "coordIndex [", 12)) ? true : false;
        }
        ptr = fgets(buf, 512, ffi);
    }
}

void CadModel::parse_point_line(char* buf)
{
    float x, y, z;
    int res, num, len;
    printf("parse_points: %s", buf);
    len = strlen(buf);
    res = sscanf(buf, "%f %f %f%n", &x, &y, &z, &num);
    printf("  len = %d, res = %d, x = %f, y = %f, z = %f, num = %d\n", len, res, x, y, z, num);
    if (res == 3) {
        add_point(x, y, z);
        if (buf[num] == ',' && (num < (len - 3))) {
            parse_point_line(buf + num + 1);
        }
    }
}

void CadModel::parse_coord_line(char* buf)
{
    int a, b, c, d;
    int res, num, len;
    printf("coords: %s", buf);
    len = strlen(buf);
    res = sscanf(buf, "%d, %d, %d, %d%n", &a, &b, &c, &d, &num);
    printf("  len = %d, res = %d, a = %d, b = %d, c = %d, d = %d, num = %d\n", len, res, a, b, c, d, num);
    if ((res == 4) && (d == -1)) {
        add_coord(a, b, c);
        if (buf[num] == ',' && (num < (len - 3))) {
            parse_coord_line(buf + num + 1);
        }
    }
}

void CadModel::add_point(float x, float y, float z)
{
    ++m_points;
}

void CadModel::add_coord(int a, int b, int c)
{
    ++m_coords;
}

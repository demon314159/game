//
// cad_model.cpp
//
#include "cad_model.h"

CadModel::CadModel(const QString& file_name)
{
    FILE* ffi = fopen(file_name.toLatin1().data(), "r");
    if (ffi == NULL) {
        printf("<<< Error opening file '%s' >>>\n", file_name.toLatin1().data());
    } else {
        printf("Open file '%s'\n", file_name.toLatin1().data());
        parse_file(ffi);
        fclose(ffi);
        printf("Close file '%s'\n", file_name.toLatin1().data());
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
    printf("points: %s", buf);
}

void CadModel::parse_coord_line(char* buf)
{
    printf("coords: %s", buf);
}

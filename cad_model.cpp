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

    ptr = fgets(buf, 512, ffi);
    while (ptr != NULL) {
        printf("%s", buf);
        ptr = fgets(buf, 512, ffi);
    }
}


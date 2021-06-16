//
// stl_model.cpp
//
#include "stl_model.h"
#include <math.h>

#define VERBOSE

StlModel::StlModel(const QString& file_name)
    : CadModel()
    , m_si(file_name)
{
#ifdef VERBOSE
    printf("StlModel(%s)\n", file_name.toLatin1().data());

    if (m_si.file_is_valid())
        printf("Successful parse of STL\n");
    else
        printf("<<< Parse of STL failed >>>\n");
    printf("Parse error message: '%s'\n", m_si.error_message().toLatin1().data());
    printf("%d facets\n", m_si.facets());
#endif
}

StlModel::~StlModel()
{
#ifdef VERBOSE
    printf("~StlModel()\n");
#endif
}

int StlModel::facets() const
{
}

float3 StlModel::facet_v1(int facet_ix) const
{
}

float3 StlModel::facet_v2(int facet_ix) const
{
}

float3 StlModel::facet_v3(int facet_ix) const
{
}

float3 StlModel::facet_color(int facet_ix) const
{
}


//
// cad_model.cpp
//
#include "cad_model.h"
#include <math.h>

#define VERBOSE

CadModel::CadModel()
{
    printf("CadModel::CadModel()\n");
}

CadModel::~CadModel()
{
    printf("~CadModel::CadModel()\n");
}

float3 CadModel::facet_normal(int facet_ix) const
{
    float3 p1, p2, p3;
    p1 = facet_v1(facet_ix);
    p2 = facet_v2(facet_ix);
    p3 = facet_v3(facet_ix);
    float3 va, vb;
    va.v1 = p2.v1 - p1.v1;
    va.v2 = p2.v2 - p1.v2;
    va.v3 = p2.v3 - p1.v3;
    vb.v1 = p3.v1 - p1.v1;
    vb.v2 = p3.v2 - p1.v2;
    vb.v3 = p3.v3 - p1.v3;
    float3 xp;
    xp.v1 = va.v2 * vb.v3 - vb.v2 * va.v3;
    xp.v2 = vb.v1 * va.v3 - va.v1 * vb.v3;
    xp.v3 = va.v1 * vb.v2 - vb.v1 * va.v2;
    return xp;
}


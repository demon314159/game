
#ifndef _ITEM_H_
#define _ITEM_H_

#include "cad_model.h"
#include "float3.h"

struct Item {
    CadModel* model;
    Float3 position;
    int action_id;
};

#endif // _ITEM_H_

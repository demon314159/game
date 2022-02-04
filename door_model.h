
#ifndef _DOOR_MODEL_H_
#define _DOOR_MODEL_H_

#include "cad_model.h"

class DoorModel: public CadModel
{
public:
    DoorModel(float dimx, float dimy, float dimz, float dimb, int vgrilles, int hgrilles, float animation_id = 0.0);
    virtual ~DoorModel();

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_dimb;
};

#endif // _DOOR_MODEL_


#ifndef _WINDOW_MODEL_H_
#define _WINDOW_MODEL_H_

#include "cad_model.h"

class WindowModel: public CadModel
{
public:
    WindowModel(float dimx, float dimy, float dimz, float dimb, int vgrilles, int hgrilles, const PaintCan& paint_can, float animation_id = 0.0);
    virtual ~WindowModel();

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_dimb;
};

#endif // _WINDOW_MODEL_

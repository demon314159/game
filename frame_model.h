
#ifndef _FRAME_MODEL_H_
#define _FRAME_MODEL_H_

#include "cad_model.h"

class FrameModel: public CadModel
{
public:
    FrameModel(float dimx, float dimy, float dimz, float dimb, float sill, float head, float jamb, const PaintCan& paint_can, float animation_id = 0.0);
    virtual ~FrameModel();

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_dimb;
    float m_sill;
    float m_head;
    float m_jamb;
    const PaintCan& m_paint_can;
    float m_animation_id;
    void define_model();
};

#endif // _FRAME_MODEL_


#include "door_model.h"
#include "frame_model.h"
#include "brick_shape.h"
#include <cstddef>

DoorModel::DoorModel(float dimx, float dimy, float dimz, float dimb, int vgrills, int hgrills, const PaintCan& paint_can, float animation_id)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_dimb(dimb)
{
    float f_sill = 0.0;
    float f_head = m_dimz / 10.0;
    float f_jamb = m_dimz / 10.0;


#ifdef NEVERMORE
    float f_rail = f_sill * 4.0;
    float f_stile = f_jamb * 4.0;
    float sill_offset = 0.75 * m_dimz / 2.0;
    float f_grille = f_jamb;
#endif
    FrameModel frame(m_dimx, m_dimy, m_dimz, m_dimb, f_sill, f_head, f_jamb, paint_can, animation_id);
    add(frame, 0.0, 0.0, 0.0);
#ifdef NEVERMORE
    FrameModel sash(m_dimx, m_dimy, f_jamb, m_dimb, f_rail, f_rail, f_stile, paint_can, animation_id);
    add(sash, 0.0, 0.0, sill_offset);
    if (vgrills > 0) {
        BrickShape vs(f_grille, m_dimy, f_grille, m_dimb);
        CadModel vgrille(vs, paint_can, animation_id);
        float dx = m_dimx - 2.0 * f_stile;
        float space = dx / (float) (vgrills + 1);
        for (int i = 0; i < vgrills; i++) {
            add(vgrille, -dx / 2.0 + space * (float) (i + 1), 0.0, sill_offset);
        }
    }

    if (hgrills > 0) {
        BrickShape hs(m_dimx, f_grille, f_grille, m_dimb);
        CadModel hgrille(hs, paint_can, animation_id);
        float dy = m_dimy - 2.0 * f_rail;
        float space = dy / (float) (hgrills + 1);
        for (int i = 0; i < hgrills; i++) {
            add(hgrille, 0.0, -dy / 2.0 + space * (float) (i + 1), sill_offset);
        }
    }
#endif
}

DoorModel::~DoorModel()
{
}





#include "door_model.h"
#include "frame_model.h"
#include "brick_shape.h"
#include "cube_shape.h"
#include "look.h"
#include <cstddef>

DoorModel::DoorModel(float dimx, float dimy, float dimz, float dimb, int vgrills, int hgrills, float animation_id)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_dimb(dimb)
{
    float f_sill = m_dimz / 40.0;
    float f_head = m_dimz / 10.0;
    float f_jamb = m_dimz / 10.0;
    float f_thickness = f_jamb * 2;


    float f_mid = dimy * 0.7;
    float f_stile = f_jamb * 4.0;
    float sill_zoffset = 0.5 * m_dimz / 2.0;

    float upper_sash_dy = m_dimy - f_mid + f_stile - m_dimb;
    float lower_sash_dy = f_mid - m_dimb;

    FrameModel frame(m_dimx, m_dimy, m_dimz, m_dimb, f_sill, f_head, f_jamb, Look::frame_paint, animation_id);
    add(frame, 0.0, 0.0, 0.0);
    FrameModel upper_sash(m_dimx - m_dimb, upper_sash_dy, f_thickness, m_dimb, f_stile, f_stile, f_stile, Look::door_paint, animation_id);
    add(upper_sash, 0.0, (m_dimy - upper_sash_dy) / 2 - m_dimb, sill_zoffset);
    FrameModel lower_sash(m_dimx - m_dimb, lower_sash_dy, f_thickness, m_dimb, f_stile, f_stile, f_stile, Look::door_paint, animation_id);
    add(lower_sash, 0.0, -(m_dimy - lower_sash_dy) / 2 + m_dimb, sill_zoffset);
    CubeShape pane(m_dimx - m_dimb, upper_sash_dy, f_jamb / 2);
    CadModel pane_model(pane, Look::glass_paint, Look::glass_animation_id);
    add(pane_model, 0.0, (m_dimy - upper_sash_dy) / 2 - m_dimb, sill_zoffset);
    CubeShape cube(m_dimx - m_dimb, f_mid, f_jamb);
    CadModel cube_model(cube, Look::door_paint, animation_id);
    add(cube_model, 0.0, -(m_dimy - f_mid) / 2, sill_zoffset);

    float f_upper_grille = 0.7 * f_jamb;
    float f_lower_grille = f_thickness;
    if (vgrills > 0) {
        BrickShape upper_vs(f_upper_grille, upper_sash_dy, f_upper_grille, m_dimb);
        BrickShape lower_vs(f_lower_grille, lower_sash_dy, f_lower_grille, m_dimb);
        CadModel upper_vgrille(upper_vs, Look::door_paint, animation_id);
        CadModel lower_vgrille(lower_vs, Look::door_paint, animation_id);

        float dx = m_dimx - 2.0 * f_stile;
        float upper_space = (dx - f_upper_grille * (float) vgrills) / (float) (vgrills + 1);
        float lower_space = (dx - f_lower_grille * (float) vgrills) / (float) (vgrills + 1);
        for (int i = 0; i < vgrills; i++) {
            add(upper_vgrille, -dx / 2.0 + (upper_space + f_upper_grille) * (float) (i + 1) - f_upper_grille / 2.0, (m_dimy - upper_sash_dy) / 2 - m_dimb, sill_zoffset);
            add(lower_vgrille, -dx / 2.0 + (lower_space + f_lower_grille) * (float) (i + 1) - f_lower_grille / 2.0, -(m_dimy - lower_sash_dy) / 2 + m_dimb, sill_zoffset);
        }
    }
    if (hgrills > 0) {
        BrickShape hs(m_dimx - m_dimb, f_upper_grille, f_upper_grille, m_dimb);
        CadModel hgrille(hs, Look::door_paint, animation_id);
        float dy = m_dimy -f_stile - f_mid;
        float space = (dy - f_upper_grille * (float) hgrills) / (float) (hgrills + 1);
        for (int i = 0; i < hgrills; i++) {
            add(hgrille, 0.0, (m_dimy - dy) / 2 - f_stile -dy / 2.0 + (space + f_upper_grille) * (float) (i + 1) - f_upper_grille / 2.0, sill_zoffset);
        }
    }
}

DoorModel::~DoorModel()
{
}




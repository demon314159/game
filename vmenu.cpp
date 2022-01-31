
#include "vmenu.h"
#include "window_model.h"
#include "door_model.h"
#include "arrow_shape.h"
#include "done_shape.h"
#include "cancel_shape.h"
#include "star_shape.h"
#include "background_shape.h"
#include "look.h"
#include "element.h"
#include "bounding_box.h"

#include <stdio.h>

Vmenu::Vmenu()
  : m_is_dirty(false)
  , m_items(0)
{
}

Vmenu::~Vmenu()
{
}
#define MAG1 0.15
CadModel Vmenu::m_model_morph = CadModel(StarShape(7, 0.5 * MAG1), Look::blue_paint, 3.0);
CadModel Vmenu::m_model_increase_height = CadModel(ArrowShape(0.5, 0.5, ArrowShape::ARROW_UP), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_decrease_height = CadModel(ArrowShape(0.5, 0.5, ArrowShape::ARROW_DOWN), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_increase_vgrilles = CadModel(ArrowShape(0.5, 0.25, ArrowShape::ARROW_RIGHT), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_decrease_vgrilles = CadModel(ArrowShape(0.5, 0.25, ArrowShape::ARROW_LEFT), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_increase_hgrilles = CadModel(ArrowShape(0.5, 0.25, ArrowShape::ARROW_UP), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_decrease_hgrilles = CadModel(ArrowShape(0.5, 0.25, ArrowShape::ARROW_DOWN), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_done = CadModel(DoneShape(0.5), Look::done_paint, 0.0);
CadModel Vmenu::m_model_cancel = CadModel(CancelShape(0.5), Look::cancel_paint, 0.0);
CadModel Vmenu::m_model_background = CadModel(BackgroundShape(0.5), Look::background_paint, 0.0);

void Vmenu::clear()
{
    m_is_dirty = m_is_dirty || (m_items > 0);
    m_items = 0;
}

void Vmenu::add_morph(Float3 position)
{
    add_item(ACTION_MORPH, position, 0);
}

void Vmenu::add_increase_height(Float3 position, int orientation)
{
    add_item(ACTION_INCREASE_HEIGHT, position, orientation);
}

void Vmenu::add_decrease_height(Float3 position, int orientation)
{
    add_item(ACTION_DECREASE_HEIGHT, position, orientation);
}

void Vmenu::add_increase_vgrilles(Float3 position, int orientation)
{
    add_item(ACTION_INCREASE_VGRILLES, position, orientation);
}

void Vmenu::add_decrease_vgrilles(Float3 position, int orientation)
{
    add_item(ACTION_DECREASE_VGRILLES, position, orientation);
}

void Vmenu::add_increase_hgrilles(Float3 position, int orientation)
{
    add_item(ACTION_INCREASE_HGRILLES, position, orientation);
}

void Vmenu::add_decrease_hgrilles(Float3 position, int orientation)
{
    add_item(ACTION_DECREASE_HGRILLES, position, orientation);
}

void Vmenu::add_done(Float3 position, int orientation)
{
    add_item(ACTION_DONE, position, orientation);
}

void Vmenu::add_cancel(Float3 position, int orientation)
{
    add_item(ACTION_CANCEL, position, orientation);
}

void Vmenu::add_item(int action_id, Float3 position, int orientation)
{
    if (m_items < MAX_ITEMS) {
        m_action[m_items] = action_id;
        m_position[m_items] = position;
        m_orientation[m_items] = orientation;
        ++m_items;
        m_is_dirty = true;
    }
}

int Vmenu::items() const
{
    return m_items;
}

void Vmenu::add_to(CadModel* model) const
{
    for (int ix = 0; ix < m_items; ix++) {
        Float3 p = m_position[ix];
        CadModel cm;
        switch (m_action[ix]) {
            case ACTION_MORPH:
                cm.add(m_model_morph);
                break;
            case ACTION_INCREASE_HEIGHT:
                cm.add(m_model_increase_height);
                cm.add(m_model_background);
                cm.add(m_model_background, 0.5);
                break;
            case ACTION_DECREASE_HEIGHT:
                cm.add(m_model_decrease_height);
                cm.add(m_model_background);
                cm.add(m_model_background, -0.5);
                break;
            case ACTION_INCREASE_VGRILLES:
                cm.add(m_model_increase_vgrilles);
                break;
            case ACTION_DECREASE_VGRILLES:
                cm.add(m_model_decrease_vgrilles);
                break;
            case ACTION_INCREASE_HGRILLES:
                cm.add(m_model_increase_hgrilles);
                break;
            case ACTION_DECREASE_HGRILLES:
                cm.add(m_model_decrease_hgrilles);
                break;
            case ACTION_DONE:
                cm.add(m_model_done);
                cm.add(m_model_background);
                cm.add(m_model_background, -0.5);
                break;
            case ACTION_CANCEL:
                cm.add(m_model_cancel);
                cm.add(m_model_background);
                cm.add(m_model_background, 0.5);
                break;
            default:
                break;
        }
        if (m_orientation[ix] == 1)
            cm.rotate_ay(90);
        else if (m_orientation[ix] == 2)
            cm.rotate_ay(180);
        else if (m_orientation[ix] == 3)
            cm.rotate_ay(270);
        model->add(cm, p.v1, p.v2, p.v3);
    }
}

bool Vmenu::is_dirty() const
{
    return m_is_dirty;
}

void Vmenu::make_clean()
{
    m_is_dirty = false;
}

void Vmenu::make_dirty()
{
    m_is_dirty = true;
}

bool Vmenu::fixed(int ix) const
{
    return m_action[ix] == ACTION_MORPH;
}

Face Vmenu::face(int ix) const
{
    Float3 pos = m_position[ix];
    BoundingBox bb;
    switch (m_action[ix]) {
        case ACTION_MORPH:
            bb = m_model_morph.bounding_box();
            break;
        case ACTION_INCREASE_HEIGHT:
            bb = m_model_increase_height.bounding_box();
            break;
        case ACTION_DECREASE_HEIGHT:
            bb = m_model_decrease_height.bounding_box();
            break;
        case ACTION_INCREASE_VGRILLES:
            bb = m_model_increase_vgrilles.bounding_box();
            break;
        case ACTION_DECREASE_VGRILLES:
            bb = m_model_decrease_vgrilles.bounding_box();
            break;
        case ACTION_INCREASE_HGRILLES:
            bb = m_model_increase_hgrilles.bounding_box();
            break;
        case ACTION_DECREASE_HGRILLES:
            bb = m_model_decrease_hgrilles.bounding_box();
            break;
        case ACTION_DONE:
            bb = m_model_done.bounding_box();
            break;
        case ACTION_CANCEL:
            bb = m_model_cancel.bounding_box();
            break;
        default:
            return {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    }
    if (m_orientation[ix] == 0 || m_orientation[ix] == 2) {
        float xlo = bb.vmin.v1 + pos.v1;
        float xhi = bb.vmax.v1 + pos.v1;
        float ylo = bb.vmin.v2 + pos.v2;
        float yhi = bb.vmax.v2 + pos.v2;
        float z = (bb.vmin.v3 + bb.vmax.v3) / 2 + pos.v3;
        return {{xlo, ylo, z}, {xlo, yhi, z}, {xhi, yhi, z}, {xhi, ylo, z}};
    } else {
        float zlo = bb.vmin.v1 + pos.v3;
        float zhi = bb.vmax.v1 + pos.v3;
        float ylo = bb.vmin.v2 + pos.v2;
        float yhi = bb.vmax.v2 + pos.v2;
        float x = (bb.vmin.v1 + bb.vmax.v1) / 2 + pos.v1;
        return {{x, ylo, zlo}, {x, yhi, zlo}, {x, yhi, zhi}, {x, ylo, zhi}};
    }
}

int Vmenu::action_id(int ix) const
{
    return m_action[ix];
}

bool Vmenu::menu_active() const
{
    for (int i = 0; i < m_items; i++) {
        if (m_action[i] == ACTION_DONE || m_action[i] == ACTION_CANCEL)
            return true;
    }
    return false;
}

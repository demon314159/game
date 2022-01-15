
#include "vmenu.h"
#include "window_model.h"
#include "door_model.h"
#include "arrow_shape.h"
#include "look.h"
#include "element.h"

#include <stdio.h>

Vmenu::Vmenu()
  : m_is_dirty(false)
  , m_items(0)
{
}

Vmenu::~Vmenu()
{
}
#define MAG1 0.5 * 0.75 * 0.5
#define MAG2 0.33 * 0.75 * 0.5
#define MAG3 0.33 * 0.75 * 0.5

CadModel Vmenu::m_model_brick = CadModel(BrickShape(MAG1 * 2.0, MAG1 * Element::dimh, MAG1 * 1.0, MAG1 * Element::dimb), Element::red_paint, 0.0);
CadModel Vmenu::m_model_window = WindowModel(MAG2 * 3, MAG2 * 6 * Element::dimh, MAG2 * 1.0, MAG2 * Element::dimb, 1, 1, Element::white_paint, 0.0);
CadModel Vmenu::m_model_door = DoorModel(MAG3 * 3, MAG3 * 8 * Element::dimh, MAG3 * 1.0, MAG3 * Element::dimb, 0, 0, Element::door_paint, 0.0);
CadModel Vmenu::m_model_increase_height = CadModel(ArrowShape(1.0, 0.5, ArrowShape::ARROW_UP), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_decrease_height = CadModel(ArrowShape(1.0, 0.5, ArrowShape::ARROW_DOWN), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_increase_vgrilles = CadModel(ArrowShape(0.5, 0.25, ArrowShape::ARROW_RIGHT), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_decrease_vgrilles = CadModel(ArrowShape(0.5, 0.25, ArrowShape::ARROW_LEFT), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_increase_hgrilles = CadModel(ArrowShape(0.5, 0.25, ArrowShape::ARROW_UP), Look::blue_paint, 0.0);
CadModel Vmenu::m_model_decrease_hgrilles = CadModel(ArrowShape(0.5, 0.25, ArrowShape::ARROW_DOWN), Look::blue_paint, 0.0);

void Vmenu::clear()
{
    m_is_dirty = (m_items > 0);
    m_items = 0;
}

void Vmenu::add_force_brick(Float3 position)
{
    add_item(ACTION_FORCE_BRICK, position);
}

void Vmenu::add_force_window(Float3 position)
{
    add_item(ACTION_FORCE_WINDOW, position);
}

void Vmenu::add_force_door(Float3 position)
{
    add_item(ACTION_FORCE_DOOR, position);
}

void Vmenu::add_increase_height(Float3 position)
{
    add_item(ACTION_INCREASE_HEIGHT, position);
}

void Vmenu::add_decrease_height(Float3 position)
{
    add_item(ACTION_DECREASE_HEIGHT, position);
}

void Vmenu::add_increase_vgrilles(Float3 position)
{
    add_item(ACTION_INCREASE_VGRILLES, position);
}

void Vmenu::add_decrease_vgrilles(Float3 position)
{
    add_item(ACTION_DECREASE_VGRILLES, position);
}

void Vmenu::add_increase_hgrilles(Float3 position)
{
    add_item(ACTION_INCREASE_HGRILLES, position);
}

void Vmenu::add_decrease_hgrilles(Float3 position)
{
    add_item(ACTION_DECREASE_HGRILLES, position);
}

void Vmenu::add_item(int action_id, Float3 position)
{
    if (m_items < MAX_ITEMS) {
        m_action[m_items] = action_id;
        m_position[m_items] = position;
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
        switch (m_action[ix]) {
            case ACTION_FORCE_BRICK:
                model->add(m_model_brick, p.v1, p.v2, p.v3);
                break;
            case ACTION_FORCE_WINDOW:
                model->add(m_model_window, p.v1, p.v2, p.v3);
                break;
            case ACTION_FORCE_DOOR:
                model->add(m_model_door, p.v1, p.v2, p.v3);
                break;
            case ACTION_INCREASE_HEIGHT:
                model->add(m_model_increase_height, p.v1, p.v2, p.v3);
                break;
            case ACTION_DECREASE_HEIGHT:
                model->add(m_model_decrease_height, p.v1, p.v2, p.v3);
                break;
            case ACTION_INCREASE_VGRILLES:
                model->add(m_model_increase_vgrilles, p.v1, p.v2, p.v3);
                break;
            case ACTION_DECREASE_VGRILLES:
                model->add(m_model_decrease_vgrilles, p.v1, p.v2, p.v3);
                break;
            case ACTION_INCREASE_HGRILLES:
                model->add(m_model_increase_hgrilles, p.v1, p.v2, p.v3);
                break;
            case ACTION_DECREASE_HGRILLES:
                model->add(m_model_decrease_hgrilles, p.v1, p.v2, p.v3);
                break;
            default:
                break;
        }
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


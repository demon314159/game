
#ifndef _VMENU_H_
#define _VMENU_H_

#include "float3.h"
#include "cad_model.h"

class Vmenu
{
    static const int ACTION_NONE = 0;
    static const int ACTION_FORCE_BRICK = 1;
    static const int ACTION_FORCE_WINDOW = 2;
    static const int ACTION_FORCE_DOOR = 3;
    static const int MAX_ITEMS = 4;
public:
    Vmenu();
    ~Vmenu();
    void clear();
    void add_to(CadModel* model) const;
    int items() const;
    bool is_dirty() const;
    void make_clean();
    void make_dirty();

    void add_force_brick(Float3 position);
    void add_force_window(Float3 position);
    void add_force_door(Float3 position);
private:
    bool m_is_dirty;
    int m_items;
    int m_action[MAX_ITEMS];
    Float3 m_position[MAX_ITEMS];
    static CadModel m_model_brick;
    static CadModel m_model_window;
    static CadModel m_model_door;

    void add_item(int action_id, Float3 position);
};

#endif // _VMENU_H_

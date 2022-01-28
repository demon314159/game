
#ifndef _VMENU_H_
#define _VMENU_H_

#include "float3.h"
#include "face.h"
#include "cad_model.h"

class Vmenu
{
public:
    static const int ACTION_NONE = 0;
    static const int ACTION_MORPH = 1;
    static const int ACTION_INCREASE_HEIGHT = 2;
    static const int ACTION_DECREASE_HEIGHT = 3;
    static const int ACTION_INCREASE_VGRILLES = 4;
    static const int ACTION_DECREASE_VGRILLES = 5;
    static const int ACTION_INCREASE_HGRILLES = 6;
    static const int ACTION_DECREASE_HGRILLES = 7;
    static const int ACTION_DONE = 8;
    static const int ACTION_CANCEL = 9;
    static const int MAX_ITEMS = 10;

    Vmenu();
    ~Vmenu();
    void clear();
    void add_to(CadModel* model) const;
    int items() const;
    bool is_dirty() const;
    void make_clean();
    void make_dirty();
    Face face(int ix) const;
    int action_id(int ix) const;
    bool menu_active() const;

    void add_morph(Float3 position, int orientation);
    void add_increase_height(Float3 position, int orientation);
    void add_decrease_height(Float3 position, int orientation);
    void add_increase_vgrilles(Float3 position, int orientation);
    void add_decrease_vgrilles(Float3 position, int orientation);
    void add_increase_hgrilles(Float3 position, int orientation);
    void add_decrease_hgrilles(Float3 position, int orientation);
    void add_done(Float3 position, int orientation);
    void add_cancel(Float3 position, int orientation);
private:
    bool m_is_dirty;
    int m_items;
    int m_action[MAX_ITEMS];
    Float3 m_position[MAX_ITEMS];
    int m_orientation[MAX_ITEMS];
    static CadModel m_model_morph;
    static CadModel m_model_increase_height;
    static CadModel m_model_decrease_height;
    static CadModel m_model_increase_vgrilles;
    static CadModel m_model_decrease_vgrilles;
    static CadModel m_model_increase_hgrilles;
    static CadModel m_model_decrease_hgrilles;
    static CadModel m_model_done;
    static CadModel m_model_cancel;
    static CadModel m_model_background;

    void add_item(int action_id, Float3 position, int orientation);
};

#endif // _VMENU_H_

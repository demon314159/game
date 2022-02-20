
#ifndef _VMENU_H_
#define _VMENU_H_

#include "float3.h"
#include "face.h"
#include "cad_model.h"

class Vmenu
{
public:
    static const int ACTION_NONE = 0;
    static const int ACTION_UNDO = 1;
    static const int ACTION_REDO = 2;
    static const int ACTION_MORPH = 3;
    static const int ACTION_INCREASE_HEIGHT = 4;
    static const int ACTION_DECREASE_HEIGHT = 5;
    static const int ACTION_INCREASE_VGRILLES = 6;
    static const int ACTION_DECREASE_VGRILLES = 7;
    static const int ACTION_INCREASE_HGRILLES = 8;
    static const int ACTION_DECREASE_HGRILLES = 9;
    static const int ACTION_DONE = 10;
    static const int ACTION_CANCEL = 11;
    static const int MAX_ITEMS = 16;

    Vmenu();
    ~Vmenu();
    void clear();
    void add_to(CadModel* model) const;
    int items() const;
    bool is_dirty() const;
    void make_clean();
    void make_dirty();
    Face face(int ix) const;
    bool fixed(int ix) const;
    int action_id(int ix) const;
    bool menu_active() const;

    void add_undo(Float3 position);
    void add_redo(Float3 position);
    void add_morph(Float3 position);
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
    static CadModel m_model_undo;
    static CadModel m_model_redo;
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

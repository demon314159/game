
#ifndef _VMENU_H_
#define _VMENU_H_

#include "item.h"

class Vmenu
{
public:
    Vmenu(int max_items);
    ~Vmenu();
    void clear();
    void add_item(CadModel* model, Float3 position, int action_id);

private:
    int m_max_items;
    int m_items;
    Item* m_item_ptr;
};

#endif // _VMENU_H_

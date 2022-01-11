
#include "vmenu.h"

#include <stdio.h>

Vmenu::Vmenu(int max_items)
  : m_max_items(max_items)
  , m_items(0)
{
    printf("Vmenu allocating %d items\n", m_max_items);
    m_item_ptr = new Item[m_max_items];
}

Vmenu::~Vmenu()
{
    printf("~Vmenu deallocating %d items\n", m_max_items);
    delete [] m_item_ptr;
}

void Vmenu::clear()
{
    m_items = 0;
}

void Vmenu::add_item(CadModel* model, Float3 position, int action_id)
{
    if (m_items < m_max_items) {
        m_item_ptr[m_items].model = model;
        m_item_ptr[m_items].position = position;
        m_item_ptr[m_items].action_id = action_id;
        ++m_items;
    }
}

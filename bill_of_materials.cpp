
#include "bill_of_materials.h"

BillOfMaterials::BillOfMaterials()
    : m_max_items(1000)
    , m_item_count(0)
{
    m_item_ptr = new Material*[m_max_items];
}

BillOfMaterials::~BillOfMaterials()
{
    for (int i = 0; i < m_max_items; i++) {
        delete [] m_item_ptr[i];
    }
    delete [] m_item_ptr;
}

int BillOfMaterials::items() const
{
    return m_item_count;
}

void BillOfMaterials::add(Material* m)
{
    if (m_item_count >= m_max_items) {
        reallocate();
    }
    m_item_ptr[m_item_count] = m;
    ++m_item_count;
}

Material* BillOfMaterials::get(int ix) const
{
    return m_item_ptr[ix];
}

void BillOfMaterials::reallocate()
{
    // this will double the value of m_max_items
    // and copy existing data to new array
    // to seamlessly keep the buffer larger than data
}



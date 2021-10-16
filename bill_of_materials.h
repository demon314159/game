
#ifndef _BILL_OF_MATERIALS_H_
#define _BILL_OF_MATERIALS_H_

#include "material.h"

class BillOfMaterials
{
public:
    BillOfMaterials();
    ~BillOfMaterials();
    int items() const;
    void add(Material* m);
    Material* get(int ix) const;

private:
    int m_max_items;
    int m_item_count;
    Material** m_item_ptr;
    void reallocate();
};

#endif // _BILL_OF_MATERIALS_H_

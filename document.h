
#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include "elements.h"

class Document
{
public:
    Document();
    ~Document();
    int elements() const;
    void add_element(ElementPtr e);
    ElementPtr get_element(int i) const;

private:
    int m_max_elements;
    int m_elements;
    ElementPtr* m_element_ptr;
    void double_the_storage();
};

#endif // _DOCUMENT_H_

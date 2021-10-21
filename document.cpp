
#include "document.h"
#include <stdio.h>

Document::Document()
    : m_max_elements(16384)
    , m_elements(0)
{
    m_element_ptr = new Element*[m_max_elements];
}

Document::~Document()
{
    for (int i = 0; i < m_elements; i++) {
        delete m_element_ptr[i];
    }
    delete [] m_element_ptr;
}

int Document::elements() const
{
    return m_elements;
}

void Document::add_element(Element* e)
{
    if (m_elements >= m_max_elements) {
        double_the_storage();
    }
    m_element_ptr[m_elements] = e;
    ++m_elements;
}

Element* Document::get_element(int i) const
{
    return m_element_ptr[i];
}

void Document::double_the_storage()
{
    // this will double the value of m_max_items
    // and copy existing data to new array
    // to seamlessly keep the buffer larger than data
    m_max_elements = 2 * m_max_elements;
    Element** temp = new Element*[m_max_elements];
    for (int i = 0; i < m_elements; i++) {
        temp[i] = m_element_ptr[i];
    }
    delete [] m_element_ptr;
    m_element_ptr = temp;
}



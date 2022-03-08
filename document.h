
#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include "element.h"
#include "token_interface.h"
#include "bounding_box.h"
#include "vertex_image.h"
#include <QString>

// Dirty means that one element has changed and only a small patch will be made to the vertex data
// Filthy means that more than one element has changed and the vertex data will be rebuilt entirely
//
// Most user edit operations only dirty the document and the image can be maintained with no lag
// add_element:  dirty
// remove_element: dirty
// unremove_element: dirty
// new: filthy
// load: filthy
// save: neither because document remains unchanged

class Element;

class Document
{
public:
    Document();
    Document(const QString& file_name);
    ~Document();
    int elements() const;
    int facets() const;
    const Element* element(int ix) const;
    void add_element(Element* e);
    void remove_element(int ix);
    void unremove_element(int ix);
    bool load(const QString& file_name, QString& error_message);
    bool save(const QString& file_name, QString& error_message) const;
    bool is_dirty() const;
    bool is_filthy() const;
    void make_clean();
    void make_dirty();
    void make_filthy();
    bool contains(Float3 pos) const;
    BoundingBox bounding_box(bool roof_filter = false) const;

private:
    bool m_is_dirty;
    bool m_is_filthy;
    int m_max_elements;
    int m_elements;
    Element** m_element_ptr;
    int* m_building_index;
    int* m_glass_index;
    VertexImage m_building;
    VertexImage m_glass;

    void double_the_storage();
    bool expect(TokenInterface& ti, const QString& pattern, QString& error_message);
    bool parse_float3(TokenInterface& ti, float& x, float& y, float& z, QString& error_message);
    bool parse_integer(TokenInterface& ti, int &v, QString& error_message);
    bool parse_float(TokenInterface& ti, float& v, QString& error_message);
    BoundingBox combine_bounding_boxes(BoundingBox bb1, BoundingBox bb2) const;
    void filter_roof(float& v) const;
};

#endif // _DOCUMENT_H_

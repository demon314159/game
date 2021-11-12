
#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include "element.h"
#include "token_interface.h"
#include "cad_model.h"
#include <QString>

class Document
{
public:
    Document();
    ~Document();
    int elements() const;
    const Element* element(int ix) const;
    void add_element(Element* e);
    void add_element(Element* e, int ix);
    Element* remove_element(int ix);
    bool load(const QString& file_name, QString& error_message);
    bool save(const QString& file_name, QString& error_message) const;
    bool last_model_valid() const;
    void build_model(CadModel* model);

private:
    bool m_last_model_valid;
    int m_max_elements;
    int m_elements;
    Element m_dummy;
    Element** m_element_ptr;

    void double_the_storage();
    bool expect(TokenInterface& ti, const QString& pattern, QString& error_message);
    bool parse_float3(TokenInterface& ti, float& x, float& y, float& z, QString& error_message);
    bool parse_integer(TokenInterface& ti, int &v, QString& error_message);
    bool parse_float(TokenInterface& ti, float& v, QString& error_message);
};

#endif // _DOCUMENT_H_

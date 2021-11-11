
#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include "element.h"
#include "token_interface.h"
#include "cad_model.h"
#include "cad_model.h"
#include <QString>

class Document
{
public:
    Document();
    ~Document();
    int elements() const;
    void add_element(Element* e, int ix);
    void add_element(Element* e);
    Element* remove_element(int ix);
    Element* get_element(int i) const;
    void save(QString& file_name) const;
    bool load(QString& file_name);
    bool error_flag() const;
    QString error_message() const;
    bool model_obsolete() const;
    void build_model(CadModel* model);

private:
    bool m_model_obsolete;
    int m_max_elements;
    int m_elements;
    Element** m_element_ptr;
    bool m_error_flag;
    QString m_error_message;

    void double_the_storage();
    bool expect(TokenInterface& ti, const QString& pattern);
    bool parse_float3(TokenInterface& ti, float& x, float& y, float& z);
    bool parse_integer(TokenInterface& ti, int &v);
    bool parse_float(TokenInterface& ti, float& v);
};

#endif // _DOCUMENT_H_

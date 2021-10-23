
#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include "elements.h"
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
    void add_element(Element* e);
    Element* get_element(int i) const;
    void save_to_file(QString& file_name) const;
    bool load_from_file(QString& file_name);
    bool error_flag() const;
    QString error_message() const;
    bool expect(TokenInterface& ti, const QString& pattern);
    bool parse_float3(TokenInterface& ti, float& x, float& y, float& z);
    bool parse_integer(TokenInterface& ti, int &v);
    bool parse_float(TokenInterface& ti, float& v);
    void build_model(CadModel* model);

private:
    int m_max_elements;
    int m_elements;
    Element** m_element_ptr;
    bool m_error_flag;
    QString m_error_message;

    void double_the_storage();
};

#endif // _DOCUMENT_H_

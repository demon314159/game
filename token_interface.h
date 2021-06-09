
#ifndef _TOKEN_INTERFACE_H_
#define _TOKEN_INTERFACE_H_

#include <QString>
#include "char_interface.h"

class TokenInterface
{
    const int TYPE_EMPTY = 0;
    const int TYPE_UNKNOWN = 1;
    const int TYPE_IDENTIFIER = 2;
    const int TYPE_UNSIGNED_INTEGER = 3;
    const int TYPE_OPERATOR = 4;
public:
    TokenInterface(const QString& file_name);
    ~TokenInterface();
    void rewind();
    void advance();
    bool is_eof() const;
    bool is_identifier() const;
    bool is_unsigned_integer() const;
    bool is_operator() const;
    QString current() const;

private:
    CharInterface m_ci;
    int m_type;
    QString m_token;
    void skip_whitespace();
    void scan_identifier();
    void scan_unsigned_integer();
    void scan_operator();
};

#endif // _TOKEN_INTERFACE_H_

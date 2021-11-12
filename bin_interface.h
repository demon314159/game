
#ifndef _BIN_INTERFACE_H_
#define _BIN_INTERFACE_H_

#include <QString>

class BinInterface
{
public:
    BinInterface(const QString& file_name);
    ~BinInterface();
    void rewind();
    void advance();
    char current() const;
    unsigned short get_unsigned_short();
    int get_int();
    float get_float();
    bool is_eof() const;

private:
    int m_pos;
    int m_size;
    char* m_buf;
};

#endif // _BIN_INTERFACE_H_

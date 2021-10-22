
#include "char_interface.h"
#include <sys/stat.h>
#include <ctype.h>

#define notVERBOSE

CharInterface::CharInterface(const QString& file_name)
    : m_pos(0)
    , m_size(0)
    , m_buf(NULL)
{
#ifdef VERBOSE
    printf("CharInterface(%s)\n", file_name.toLatin1().data());
#endif
    FILE* ffi = fopen(file_name.toLatin1().data(), "r");
    if (ffi == NULL) {
#ifdef VERBOSE
        printf("<<< Error opening file '%s' >>>\n", file_name.toLatin1().data());
#endif
    } else {
        struct stat st;
        stat(file_name.toLatin1().data(), &st);
        m_size = st.st_size;
        m_buf = new char[m_size];
#ifdef VERBOSE
        printf("Size of file = %d\n", m_size);
#endif
        int n = fread(m_buf, 1, m_size, ffi);
        fclose(ffi);
#ifdef VERBOSE
        printf("Chars read = %d\n", n);
#endif
        if (n != m_size) {
            m_size = 0;
        }
    }
}

CharInterface::~CharInterface()
{
#ifdef VERBOSE
    printf("~CharInterface()\n");
#endif
    if (m_buf != NULL) {
        delete [] m_buf;
    }
}

void CharInterface::rewind()
{
    m_pos = 0;
}

void CharInterface::advance()
{
    if (m_pos < m_size) {
        ++m_pos;
    }
}

char CharInterface::current() const
{
    if (m_pos < m_size) {
        return m_buf[m_pos];
    } else {
        return ' ';
    }
}

bool CharInterface::is_eof() const
{
    return m_pos >= m_size;
}

bool CharInterface::is_eol1() const
{
    if (m_pos < m_size) {
        return m_buf[m_pos] == 0x0a;
    }
    return false;
}

bool CharInterface::is_eol2() const
{
    if (m_pos < m_size) {
        return m_buf[m_pos] == 0x0d;
    }
    return false;
}

bool CharInterface::is_blank() const
{
    if (m_pos < m_size) {
        return isblank(m_buf[m_pos]);
    }
    return false;
}

bool CharInterface::is_alpha() const
{
    if (m_pos < m_size) {
        return isalpha(m_buf[m_pos]) || m_buf[m_pos] == '_';
    }
    return false;
}

bool CharInterface::is_digit() const
{
    if (m_pos < m_size) {
        return isdigit(m_buf[m_pos]);
    }
    return false;
}

bool CharInterface::is_symbol() const
{
    if (m_pos < m_size) {
        return ispunct(m_buf[m_pos]) && m_buf[m_pos] != '_';
    }
    return false;
}

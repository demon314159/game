
#include "token_interface.h"

#define VERBOSE

TokenInterface::TokenInterface(const QString& file_name)
    : m_ci(file_name)
    , m_type(TYPE_EMPTY)
    , m_token("")
{
#ifdef VERBOSE
    printf("TokenInterface(%s)\n", file_name.toLatin1().data());
#endif
}

TokenInterface::~TokenInterface()
{
#ifdef VERBOSE
    printf("~TokenInterface()\n");
#endif
}

void TokenInterface::rewind()
{
    m_ci.rewind();
    m_token = "";
    m_type = TYPE_EMPTY;
}

void TokenInterface::advance()
{
    skip_whitespace();
    m_token = "";
    m_type = TYPE_EMPTY;
    if (m_ci.is_eof()) {
        return;
    } else if (m_ci.is_alpha()) {
        scan_identifier();
    } else if (m_ci.is_digit()) {
        scan_unsigned_integer();
    } else if (m_ci.is_symbol()) {
        scan_operator();
    }
}

bool TokenInterface::is_eof() const
{
    return m_ci.is_eof();
}

QString TokenInterface::current() const
{
    return m_token;
}

void TokenInterface::skip_whitespace()
{
    bool in_comment = m_ci.current() == '#';

    while (in_comment || (!m_ci.is_alpha() && !m_ci.is_digit() && !m_ci.is_symbol() && !m_ci.is_eof())) {
        m_ci.advance();
        if (m_ci.is_eol1() || m_ci.is_eol2()) {
            in_comment = false;
        } else if (m_ci.current() == '#') {
            in_comment = true;
        }
    }
}

void TokenInterface::scan_identifier()
{
    m_type = TYPE_IDENTIFIER;
    m_token = m_ci.current();
    m_ci.advance();
    while (m_ci.is_alpha() || m_ci.is_digit()) {
        m_token += m_ci.current();
        m_ci.advance();
    }
}

void TokenInterface::scan_unsigned_integer()
{
    m_type = TYPE_UNSIGNED_INTEGER;
    m_token = m_ci.current();
    m_ci.advance();
    while (m_ci.is_digit()) {
        m_token += m_ci.current();
        m_ci.advance();
    }
}

void TokenInterface::scan_operator()
{
    m_type = TYPE_OPERATOR;
    m_token = m_ci.current();
    m_ci.advance();
}

bool TokenInterface::is_identifier() const
{
    return m_type == TYPE_IDENTIFIER;
}

bool TokenInterface::is_unsigned_integer() const
{
    return m_type == TYPE_UNSIGNED_INTEGER;
}

bool TokenInterface::is_operator() const
{
    return m_type == TYPE_OPERATOR;
}


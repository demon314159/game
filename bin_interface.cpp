
#include "bin_interface.h"
#include <QFile>
#include <QDataStream>

#define notVERBOSE

BinInterface::BinInterface(const QString& file_name)
    : m_pos(0)
    , m_size(0)
    , m_buf(NULL)
{
#ifdef VERBOSE
    printf("BinInterface(%s)\n", file_name.toLatin1().data());
#endif

    if (!QFile::exists(file_name)) {
#ifdef VERBOSE
        printf("<<< File not found '%s' >>>\n", file_name.toLatin1().data());
#endif
        return;
    }

    QFile ffi(file_name);
    if (!ffi.open(QIODevice::ReadOnly)) {
#ifdef VERBOSE
        printf("<<< Error opening file '%s' >>>\n", file_name.toLatin1().data());
#endif
        return;
    }

    m_size = ffi.size();
    if (m_size == 0) {
#ifdef VERBOSE
        printf("<<< File is empty '%s' >>>\n", file_name.toLatin1().data());
#endif
        return;
    }

    m_buf = new char[m_size];
#ifdef VERBOSE
    printf("Size of file = %d\n", m_size);
#endif
    QDataStream ds(&ffi);
    int n = ds.readRawData(m_buf, m_size);
    ffi.close();
    if (n != m_size) {
#ifdef VERBOSE
        printf("<<< Expecting %d bytes but read %d bytes >>>\n", m_size, n);
#endif
        m_size = 0;
        return;
    } else {
#ifdef VERBOSE
    printf("Bytes read = %d\n", n);
#endif
    }
}

BinInterface::~BinInterface()
{
#ifdef VERBOSE
    printf("~BinInterface()\n");
#endif
    if (m_buf != NULL) {
        delete [] m_buf;
    }
}

void BinInterface::rewind()
{
    m_pos = 0;
}

void BinInterface::advance()
{
    if (m_pos < m_size) {
        ++m_pos;
    }
}

char BinInterface::current() const
{
    if (m_pos < m_size) {
        return m_buf[m_pos];
    } else {
        return 0;
    }
}

bool BinInterface::is_eof() const
{
    return m_pos >= m_size;
}

unsigned short BinInterface::get_unsigned_short()
{
    if (m_pos < (m_size - 1)) {
        unsigned short* v = (unsigned short*) &m_buf[m_pos];
        m_pos += 2;
        return *v;
    } else {
        printf("\n<<< BinInterface::get_unsigned_short() past end of file should never happen >>>\n");
        return 0;
    }
}

int BinInterface::get_int()
{
    if (m_pos < (m_size - 3)) {
        int* v = (int*) &m_buf[m_pos];
        m_pos += 4;
        return *v;
    } else {
        printf("\n<<< BinInterface::get_int() past end of file should never happen >>>\n");
        return 0;
    }
}

float BinInterface::get_float()
{
    if (m_pos < (m_size - 3)) {
        float* v = (float*) &m_buf[m_pos];
        m_pos += 4;
        return *v;
    } else {
        printf("\n<<< BinInterface::get_float() past end of file should never happen >>>\n");
        return 0;
    }
}



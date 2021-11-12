
#ifndef _STL_INTERFACE_H_
#define _STL_INTERFACE_H_

#include <QString>
#include "bin_interface.h"
#include "float3.h"
#include "int3.h"

class StlInterface
{
public:
    StlInterface(const QString& file_name);
    ~StlInterface();
    bool file_is_valid() const;
    QString error_message() const;
    int facets() const;
    float3 facet_v1(int facet_ix) const;
    float3 facet_v2(int facet_ix) const;
    float3 facet_v3(int facet_ix) const;

private:
    bool m_file_is_valid;
    bool m_pass2;
    BinInterface m_bi;
    QString m_error_message;
    int m_facet_count;
    float3* m_v1;
    float3* m_v2;
    float3* m_v3;

    bool parse();
};

#endif // _STL_INTERFACE_H_

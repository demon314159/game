
#include "vertex_image.h"

VertexImage::VertexImage(int initial_max_vertex_count)
    : m_max_vertex_count(initial_max_vertex_count)
    , m_vertex_count(0)
{
    m_vertex_data = new VertexData[m_max_vertex_count];
}

VertexImage::~VertexImage()
{
    delete [] m_vertex_data;
}

int VertexImage::max_vertex_count() const
{
    return m_max_vertex_count;
}

void VertexImage::set_max_vertex_count(int n)
{
    m_max_vertex_count = n;
    VertexData* tt = new VertexData[n];
    for (int i = 0; i < m_vertex_count; i++) {
        tt[i] = m_vertex_data[i];
    }
    delete[] m_vertex_data;
    m_vertex_data = tt;
}

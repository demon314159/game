
#include "vertex_image.h"

VertexImage::VertexImage(int initial_storage)
    : m_storage(initial_storage)
{
}

VertexImage::~VertexImage()
{
}

int VertexImage::storage() const
{
    return m_storage;
}

void VertexImage::set_storage(int n)
{
}


#include "vertex_image.h"
#include "cad_model.h"

VertexImage::VertexImage()
    : m_max_vertex_count(INITIAL_MAX_VERTEX_COUNT)
    , m_vertex_count(0)
{
    m_vertex_data = new VertexData[m_max_vertex_count];
}

VertexImage::~VertexImage()
{
    delete [] m_vertex_data;
}

int VertexImage::vertex_count() const
{
    return m_vertex_count;
}

void VertexImage::add_element(Element* e, bool transparent)
{
    float an_id;
    Float3 vp, vc, vn;
    VertexData vd;
    if (e == NULL)
        return;
    Float3 pos = e->pos();
    const CadModel& model = e->model();
    for (int i = 0; i < model.facets(); i++) {
        an_id = model.facet_animation_id(i);
        if ((transparent && (an_id == 99.0)) || (!transparent && (an_id != 99.0))) {
            vc = model.facet_color(i);
            vn = model.facet_normal(i);
            vd.animation_id = an_id;

            vp = model.facet_v1(i);
            vd.position = QVector3D(vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3);
            vd.normal = QVector3D(vn.v1, vn.v2, vn.v3);
            vd.color = QVector3D(vc.v1, vc.v2, vc.v3);
            add_vertex(vd);

            vp = model.facet_v2(i);
            vd.position = QVector3D(vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3);
            vd.normal = QVector3D(vn.v1, vn.v2, vn.v3);
            vd.color = QVector3D(vc.v1, vc.v2, vc.v3);
            add_vertex(vd);

            vp = model.facet_v3(i);
            vd.position = QVector3D(vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3);
            vd.normal = QVector3D(vn.v1, vn.v2, vn.v3);
            vd.color = QVector3D(vc.v1, vc.v2, vc.v3);
            add_vertex(vd);
        }
    }
}

void VertexImage::add_vertex(VertexData& vd)
{
    if (m_vertex_count >= m_max_vertex_count)
        double_the_storage();
    m_vertex_data[m_vertex_count] = vd;
    ++m_vertex_count;
}

void VertexImage::double_the_storage()
{
    // this will double the value of m_max_items
    // and copy existing data to new array
    // to seamlessly keep the buffer larger than data
    m_max_vertex_count = 2 * m_max_vertex_count;
    VertexData* temp = new VertexData[m_max_vertex_count];
    for (int i = 0; i < m_vertex_count; i++) {
        temp[i] = m_vertex_data[i];
    }
    delete [] m_vertex_data;
    m_vertex_data = temp;
}

void VertexImage::update_element(int start_ix, const Element* e, bool transparent)
{
    float dd = 0.04;
    float dx = dd * 10;
    float an_id;
    Float3 vp, vc, vn;
    VertexData vd;
    if (e == NULL)
        return;
    Float3 pos = e->pos();
    bool removed = e->removed();
    const CadModel& model = e->model();
    for (int i = 0; i < model.facets(); i++) {
        an_id = model.facet_animation_id(i);
        if ((transparent && (an_id == 99.0)) || (!transparent && (an_id != 99.0))) {
            vc = model.facet_color(i);
            vn = model.facet_normal(i);
            vd.animation_id = removed ? 3.0 : an_id;

            if (removed)
                vp = {-dx, -dd, 0.0};
            else
                vp = model.facet_v1(i);
            vd.position = QVector3D(vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3);
            vd.normal = QVector3D(vn.v1, vn.v2, vn.v3);
            vd.color = QVector3D(vc.v1, vc.v2, vc.v3);
            m_vertex_data[start_ix++] = vd;

            if (removed)
                vp = {-dx - dd, -2 * dd, 0.0};
            else
                vp = model.facet_v2(i);
            vd.position = QVector3D(vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3);
            vd.normal = QVector3D(vn.v1, vn.v2, vn.v3);
            vd.color = QVector3D(vc.v1, vc.v2, vc.v3);
            m_vertex_data[start_ix++] = vd;

            if (removed)
                vp = {-dx + dd, -2 * dd, 0.0};
            else
                vp = model.facet_v3(i);
            vd.position = QVector3D(vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3);
            vd.normal = QVector3D(vn.v1, vn.v2, vn.v3);
            vd.color = QVector3D(vc.v1, vc.v2, vc.v3);
            m_vertex_data[start_ix++] = vd;
        }
    }
}



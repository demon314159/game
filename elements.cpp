
#include "elements.h"
#include "window_model.h"
#include <stdio.h>

Element::Element(float3 pos)
    : m_pos(pos)
{
}

Element::~Element()
{
}

void Element::save_to_file(QDataStream& ds) const
{
    QString msg = QString("%1, %2, %3").arg(m_pos.v1).arg(m_pos.v2).arg(m_pos.v3);
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}

float3 Element::get_pos() const
{
    float3 pos;
    pos.v1 = m_pos.v1 * dimw;
    pos.v2 = m_pos.v2 * dimh;
    pos.v3 = m_pos.v3 * dimw;
    return pos;
}

CadModel& Element::get_model()
{
    return m_default_model;
}

PaintCan Element::red_paint(1.0, 0.0, 0.0);
PaintCan Element::white_paint(1.0, 1.0, 1.0);
CadModel Element::m_default_model(BrickShape(Element::dimw, Element::dimh, Element::dimw, Element::dimb), Element::red_paint, 0.0);

CadModel BrickElement::m_model_ns = CadModel(BrickShape(2.0 * Element::dimw, Element::dimh, Element::dimw, Element::dimb), Element::red_paint, 0.0);
CadModel BrickElement::m_model_ew = CadModel(BrickShape(Element::dimw, Element::dimh, 2.0 * Element::dimw, Element::dimb), Element::red_paint, 0.0);
HalfBrickElement::HalfBrickElement(float xpos, float ypos, float zpos)
    : Element({xpos, ypos, zpos})
{
}

void HalfBrickElement::save_to_file(QDataStream& ds) const
{
    QString msg = "HalfBrick(";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    Element::save_to_file(ds);
    msg = ")\n";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}

BrickElement::BrickElement(float xpos, float ypos, float zpos, int orientation)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
{

}

CadModel& BrickElement::get_model()
{
    if (m_orientation == 0 || m_orientation == 2)
        return m_model_ns;
    return m_model_ew;
}

void BrickElement::save_to_file(QDataStream& ds) const
{
    QString msg = "Brick(";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    Element::save_to_file(ds);
    msg = QString(", %1)\n").arg(m_orientation);
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}

WindowElement::WindowElement(float xpos, float ypos, float zpos, int orientation,
                             int width, int height, int hgrilles, int vgrilles)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
    , m_width(width)
    , m_height(height)
    , m_hgrilles(hgrilles)
    , m_vgrilles(vgrilles)
    , m_model(WindowModel(width * dimw, height * dimh, dimw, dimb, vgrilles, hgrilles, white_paint, 0.0))
{
    if (orientation == 1)
        m_model.rotate_ay(90.0);
    else if (orientation == 2)
        m_model.rotate_ay(180.0);
    else if (orientation == 3)
        m_model.rotate_ay(270.0);
}

void WindowElement::save_to_file(QDataStream& ds) const
{
    QString msg = "Window(";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    Element::save_to_file(ds);
    msg = QString(", %1, %2, %3, %4, %5)\n").arg(m_orientation).arg(m_width).arg(m_height).arg(m_hgrilles).arg(m_vgrilles);
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}

CadModel& WindowElement::get_model()
{
    return m_model;
}




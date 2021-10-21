
#include "elements.h"
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
{
}

void WindowElement::save_to_file(QDataStream& ds) const
{
    QString msg = "Window(";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    Element::save_to_file(ds);
    msg = QString(", %1, %2, %3, %4, %5)\n").arg(m_orientation).arg(m_width).arg(m_height).arg(m_hgrilles).arg(m_vgrilles);
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}




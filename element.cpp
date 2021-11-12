
#include "element.h"
#include "brick_shape.h"
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
    pos.v1 = m_pos.v1;
    pos.v2 = m_pos.v2;
    pos.v3 = m_pos.v3;
    return pos;
}

CadModel& Element::model()
{
    return m_default_model;
}

Face Element::gen_face(float xf, float yf, float zf) const
{
    Face f;
    f.v1.v1 = (m_pos.v1 - xf);
    f.v1.v2 = (m_pos.v2 + yf) * dimh;
    f.v1.v3 = (m_pos.v3 - zf);
    f.v2.v1 = (m_pos.v1 - xf);
    f.v2.v2 = (m_pos.v2 + yf) * dimh;
    f.v2.v3 = (m_pos.v3 + zf);
    f.v3.v1 = (m_pos.v1 + xf);
    f.v3.v2 = (m_pos.v2 + yf) * dimh;
    f.v3.v3 = (m_pos.v3 + zf);
    f.v4.v1 = (m_pos.v1 + xf);
    f.v4.v2 = (m_pos.v2 + yf) * dimh;
    f.v4.v3 = (m_pos.v3 - zf);
    return f;
}

Face Element::gen_sub_face(float xf, float yf, float zf, float xoff, float zoff) const
{
    Face f;
    f.v1.v1 = (m_pos.v1 - xf + xoff);
    f.v1.v2 = (m_pos.v2 + yf) * dimh;
    f.v1.v3 = (m_pos.v3 - zf + zoff);
    f.v2.v1 = (m_pos.v1 - xf + xoff);
    f.v2.v2 = (m_pos.v2 + yf) * dimh;
    f.v2.v3 = (m_pos.v3 - zf + zoff + 1.0);
    f.v3.v1 = (m_pos.v1 - xf + xoff + 1.0);
    f.v3.v2 = (m_pos.v2 + yf) * dimh;
    f.v3.v3 = (m_pos.v3 - zf + zoff + 1.0);
    f.v4.v1 = (m_pos.v1 - xf + xoff + 1.0);
    f.v4.v2 = (m_pos.v2 + yf) * dimh;
    f.v4.v3 = (m_pos.v3 - zf + zoff);
    return f;
}

bool Element::gen_contains(float3 pos, float xf, float yf, float zf) const
{
    if (pos.v1 < (m_pos.v1 - xf))
        return false;
    if (pos.v1 > (m_pos.v1 + xf))
        return false;
    if (pos.v2 < (m_pos.v2 - yf))
        return false;
    if (pos.v2 > (m_pos.v2 + yf))
        return false;
    if (pos.v3 < (m_pos.v3 - zf))
        return false;
    if (pos.v3 > (m_pos.v3 + zf))
        return false;
    return true;
}

float Element::top_level() const
{
    return m_pos.v2 + 0.5;
}

Face Element::top_face() const
{
    return gen_face(0.5, 0.5, 0.5);
}

int Element::sub_face_count() const
{
    return 1;  // Default half-brick
}

Face Element::top_sub_face(int ix) const
{
    (void) ix;
    return top_face();
}

bool Element::contains(float3 pos) const
{
    return gen_contains(pos, 0.5, 0.5, 0.5);
}

PaintCan Element::red_paint(1.0, 0.0, 0.0);
PaintCan Element::white_paint(1.0, 1.0, 1.0);
PaintCan Element::gray_paint(0.8, 0.8, 0.8);
CadModel Element::m_default_model(BrickShape(1.0, Element::dimh, 1.0, Element::dimb), Element::red_paint, 0.0);

CadModel BrickElement::m_model_ns = CadModel(BrickShape(2.0, Element::dimh, 1.0, Element::dimb), Element::red_paint, 0.0);
CadModel BrickElement::m_model_ew = CadModel(BrickShape(1.0, Element::dimh, 2.0, Element::dimb), Element::red_paint, 0.0);
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

CadModel& BrickElement::model()
{
    if (m_orientation == 0 || m_orientation == 2)
        return m_model_ns;
    return m_model_ew;
}

Face BrickElement::top_face() const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? 1.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : 1.0;
    return gen_face(xf, yf, zf);
}

int BrickElement::sub_face_count() const
{
    return 2;  // full brick
}

Face BrickElement::top_sub_face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? 1.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : 1.0;
    float xoff = (m_orientation == 0 || m_orientation == 2) ? (float) ix : 0.0;
    float zoff = (m_orientation == 0 || m_orientation == 2) ? 0.0 : (float) ix;
    return gen_sub_face(xf, yf, zf, xoff, zoff);
}

bool BrickElement::contains(float3 pos) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? 1.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : 1.0;
    return gen_contains(pos, xf, yf, zf);
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
    , m_model(WindowModel(width, height * dimh, 1.0, dimb, vgrilles, hgrilles, white_paint, 0.0))
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

CadModel& WindowElement::model()
{
    return m_model;
}

float WindowElement::top_level() const
{
    float3 pos = get_pos();
    return pos.v2 + m_height / 2.0;
}

Face WindowElement::top_face() const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = m_height / 2.0;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_face(xf, yf, zf);
}

int WindowElement::sub_face_count() const
{
    return m_width;
}

Face WindowElement::top_sub_face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = m_height / 2.0;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    float xoff = (m_orientation == 0 || m_orientation == 2) ? (float) ix : 0.0;
    float zoff = (m_orientation == 0 || m_orientation == 2) ? 0.0 : (float) ix;
    return gen_sub_face(xf, yf, zf, xoff, zoff);
}

bool WindowElement::contains(float3 pos) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = m_height / 2.0;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_contains(pos, xf, yf, zf);
}

LedgeElement::LedgeElement(float xpos, float ypos, float zpos, int orientation, int width)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
    , m_width(width)
    , m_model(BrickShape(width, dimh, 1.0, dimb), gray_paint, 0.0)
{
    if (orientation == 1)
        m_model.rotate_ay(90.0);
    else if (orientation == 2)
        m_model.rotate_ay(180.0);
    else if (orientation == 3)
        m_model.rotate_ay(270.0);
}

void LedgeElement::save_to_file(QDataStream& ds) const
{
    QString msg = "Ledge(";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    Element::save_to_file(ds);
    msg = QString(", %1, %2)\n").arg(m_orientation).arg(m_width);
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}

CadModel& LedgeElement::model()
{
    return m_model;
}

Face LedgeElement::top_face() const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_face(xf, yf, zf);
}

int LedgeElement::sub_face_count() const
{
    return m_width;
}

Face LedgeElement::top_sub_face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    float xoff = (m_orientation == 0 || m_orientation == 2) ? (float) ix : 0.0;
    float zoff = (m_orientation == 0 || m_orientation == 2) ? 0.0 : (float) ix;
    return gen_sub_face(xf, yf, zf, xoff, zoff);
}

bool LedgeElement::contains(float3 pos) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_contains(pos, xf, yf, zf);
}


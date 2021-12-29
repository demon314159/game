
#include "element.h"
#include "brick_shape.h"
#include "gable_brick_shape.h"
#include "window_model.h"
#include "door_model.h"
#include <stdio.h>

Element::Element(Float3 pos)
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

Float3 Element::get_pos() const
{
    Float3 pos;
    pos.v1 = m_pos.v1;
    pos.v2 = m_pos.v2;
    pos.v3 = m_pos.v3;
    return pos;
}

int Element::orientation() const
{
    return 0;
}

const CadModel& Element::model() const
{
    return m_default_model;
}

Float3 Element::face_vertex(float xf, float yf, float zf) const
{
    Float3 v;
    v.v1 = (m_pos.v1 + xf);
    v.v2 = (m_pos.v2 + yf) * dimh;
    v.v3 = (m_pos.v3 + zf);
    return v;
}

Face Element::gen_top_sub_face(float xf, float yf, float zf, float xoff, float zoff) const
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

bool Element::gen_contains(Float3 pos, float xf, float yf, float zf, bool gable) const
{
    if (pos.v1 < (m_pos.v1 - xf))
        return false;
    if (pos.v1 > (m_pos.v1 + xf))
        return false;
    if (pos.v2 < (m_pos.v2 - yf))
        return false;
    if (gable) {
        if (pos.v2 > (m_pos.v2))
            return false;
    } else {
        if (pos.v2 > (m_pos.v2 + yf))
            return false;
    }
    if (pos.v3 < (m_pos.v3 - zf))
        return false;
    if (pos.v3 > (m_pos.v3 + zf))
        return false;
    return true;
}

Face Element::gen_face(int ix, float xf, float yf, float zf) const
{
    return common_gen_face(ix, xf, yf, zf, false, 0);
}

Face Element::gen_gable_face(int ix, float xf, float yf, float zf, int orientation) const
{
    return common_gen_face(ix, xf, yf, zf, true, orientation);
}

Face Element::common_gen_face(int ix, float xf, float yf, float zf, bool gable_flag, int orientation) const
{
    Face f;
    Float3 v_lbl = face_vertex(-xf, -yf, -zf);
    Float3 v_lfl = face_vertex(-xf, -yf, zf);
    Float3 v_lfr = face_vertex(xf, -yf, zf);
    Float3 v_lbr = face_vertex(xf, -yf, -zf);
    Float3 v_ubl = face_vertex(-xf, yf, -zf);
    Float3 v_ufl = face_vertex(-xf, yf, zf);
    Float3 v_ufr = face_vertex(xf, yf, zf);
    Float3 v_ubr = face_vertex(xf, yf, -zf);

    if (gable_flag) {
        if (orientation == 0) {
            v_ubl.v2 = v_lbl.v2 + dimb * dimh;
            v_ufl.v2 = v_lfl.v2 + dimb * dimh;
        };
        if (orientation == 1) {
            v_ufl.v2 = v_lfl.v2 + dimb * dimh;
            v_ufr.v2 = v_lfr.v2 + dimb * dimh;
        };
        if (orientation == 2) {
           v_ufr.v2 = v_lfr.v2 + dimb * dimh;
           v_ubr.v2 = v_lbr.v2 + dimb * dimh;
        };
        if (orientation == 3) {
            v_ubl.v2 = v_lbl.v2 + dimb * dimh;
            v_ubr.v2 = v_lbr.v2 + dimb * dimh;
        };
    }
    if (ix == TOP_FACE) {
        f.v1 = v_ubl;
        f.v2 = v_ufl;
        f.v3 = v_ufr;
        f.v4 = v_ubr;
    } else if (ix == BOTTOM_FACE) {
        f.v1 = v_lbl;
        f.v2 = v_lfl;
        f.v3 = v_lfr;
        f.v4 = v_lbr;
    } else if (ix == LEFT_FACE) {
        f.v1 = v_lbl;
        f.v2 = v_lfl;
        f.v3 = v_ufl;
        f.v4 = v_ubl;
    } else if (ix == RIGHT_FACE) {
        f.v1 = v_lbr;
        f.v2 = v_lfr;
        f.v3 = v_ufr;
        f.v4 = v_ubr;
    } else if (ix == FRONT_FACE) {
        f.v1 = v_lfl;
        f.v2 = v_lfr;
        f.v3 = v_ufr;
        f.v4 = v_ufl;
    } else { // BACK_FACE
        f.v1 = v_lbl;
        f.v2 = v_lbr;
        f.v3 = v_ubr;
        f.v4 = v_ubl;
    }
    return f;
}

float Element::top_level() const
{
    return m_pos.v2 + 0.5;
}

float Element::bottom_level() const
{
    return m_pos.v2 - 0.5;
}

Face Element::face(int ix) const
{
    return gen_face(ix, 0.5, 0.5, 0.5);
}

int Element::sub_face_count() const
{
    return 1;  // Default half-brick
}

Face Element::top_sub_face(int ix) const
{
    (void) ix;
    return face(TOP_FACE);
}

bool Element::contains(Float3 pos) const
{
    return gen_contains(pos, 0.5, 0.5, 0.5);
}

PaintCan Element::red_paint(1.0, 0.0, 0.0);
PaintCan Element::white_paint(1.0, 1.0, 1.0);
PaintCan Element::door_paint(0.2, 1.0, 0.2);
PaintCan Element::gray_paint(0.8, 0.8, 0.8);
CadModel Element::m_default_model(BrickShape(1.0, Element::dimh, 1.0, Element::dimb), Element::red_paint, 0.0);

CadModel BrickElement::m_model_ns = CadModel(BrickShape(2.0, Element::dimh, 1.0, Element::dimb), Element::red_paint, 0.0);
CadModel BrickElement::m_model_ew = CadModel(BrickShape(1.0, Element::dimh, 2.0, Element::dimb), Element::red_paint, 0.0);

CadModel GableBrickElement::m_model_qns = CadModel(GableBrickShape(1.0, Element::dimh, 1.0, Element::dimb, 0), Element::red_paint, 0.0);
CadModel GableBrickElement::m_model_qew = CadModel(GableBrickShape(1.0, Element::dimh, 1.0, Element::dimb, 1), Element::red_paint, 0.0);
CadModel GableBrickElement::m_model_qsn = CadModel(GableBrickShape(1.0, Element::dimh, 1.0, Element::dimb, 2), Element::red_paint, 0.0);
CadModel GableBrickElement::m_model_qwe = CadModel(GableBrickShape(1.0, Element::dimh, 1.0, Element::dimb, 3), Element::red_paint, 0.0);

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

const CadModel& BrickElement::model() const
{
    if (m_orientation == 0 || m_orientation == 2)
        return m_model_ns;
    return m_model_ew;
}

Face BrickElement::face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? 1.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : 1.0;
    return gen_face(ix, xf, yf, zf);
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
    return gen_top_sub_face(xf, yf, zf, xoff, zoff);
}

bool BrickElement::contains(Float3 pos) const
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

int BrickElement::orientation() const
{
    return m_orientation;
}

GableBrickElement::GableBrickElement(float xpos, float ypos, float zpos, int orientation)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
{

}

const CadModel& GableBrickElement::model() const
{
    if (m_orientation == 0)
        return m_model_qns;
    if (m_orientation == 1)
        return m_model_qew;
    if (m_orientation == 2)
        return m_model_qsn;
    return m_model_qwe;
}

void GableBrickElement::save_to_file(QDataStream& ds) const
{
    QString msg = "GableBrick(";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    Element::save_to_file(ds);
    msg = QString(", %1)\n").arg(m_orientation);
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}

Face GableBrickElement::face(int ix) const
{
    float xf = 0.5;
    float yf = 0.5;
    float zf = 0.5;
    return gen_gable_face(ix, xf, yf, zf, m_orientation);
}

Face GableBrickElement::top_sub_face(int ix) const
{
    (void) ix;
    return face(TOP_FACE);
}

bool GableBrickElement::contains(Float3 pos) const
{
    float xf = 0.5;
    float yf = 0.5;
    float zf = 0.5;
    return gen_contains(pos, xf, yf, zf, true);
}

int GableBrickElement::orientation() const
{
    return m_orientation;
}

DoorElement::DoorElement(float xpos, float ypos, float zpos, int orientation,
                             int width, int height, int hgrilles, int vgrilles)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
    , m_width(width)
    , m_height(height)
    , m_hgrilles(hgrilles)
    , m_vgrilles(vgrilles)
    , m_model(DoorModel(width, height * dimh, 1.0, dimb, vgrilles, hgrilles, door_paint, 0.0))
{
    if (orientation == 1)
        m_model.rotate_ay(90.0);
    else if (orientation == 2)
        m_model.rotate_ay(180.0);
    else if (orientation == 3)
        m_model.rotate_ay(270.0);
}

void DoorElement::save_to_file(QDataStream& ds) const
{
    QString msg = "Door(";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    Element::save_to_file(ds);
    msg = QString(", %1, %2, %3, %4, %5)\n").arg(m_orientation).arg(m_width).arg(m_height).arg(m_hgrilles).arg(m_vgrilles);
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}

const CadModel& DoorElement::model() const
{
    return m_model;
}

float DoorElement::top_level() const
{
    Float3 pos = get_pos();
    return pos.v2 + m_height / 2.0;
}

float DoorElement::bottom_level() const
{
    Float3 pos = get_pos();
    return pos.v2 - m_height / 2.0;
}

Face DoorElement::face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = m_height / 2.0;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_face(ix, xf, yf, zf);
}

int DoorElement::sub_face_count() const
{
    return m_width;
}

Face DoorElement::top_sub_face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = m_height / 2.0;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    float xoff = (m_orientation == 0 || m_orientation == 2) ? (float) ix : 0.0;
    float zoff = (m_orientation == 0 || m_orientation == 2) ? 0.0 : (float) ix;
    return gen_top_sub_face(xf, yf, zf, xoff, zoff);
}

bool DoorElement::contains(Float3 pos) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = m_height / 2.0;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_contains(pos, xf, yf, zf);
}

int DoorElement::orientation() const
{
    return m_orientation;
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

const CadModel& WindowElement::model() const
{
    return m_model;
}

float WindowElement::top_level() const
{
    Float3 pos = get_pos();
    return pos.v2 + m_height / 2.0;
}

float WindowElement::bottom_level() const
{
    Float3 pos = get_pos();
    return pos.v2 - m_height / 2.0;
}

Face WindowElement::face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = m_height / 2.0;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_face(ix, xf, yf, zf);
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
    return gen_top_sub_face(xf, yf, zf, xoff, zoff);
}

bool WindowElement::contains(Float3 pos) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = m_height / 2.0;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_contains(pos, xf, yf, zf);
}

int WindowElement::orientation() const
{
    return m_orientation;
}



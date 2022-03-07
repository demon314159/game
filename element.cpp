
#include "element.h"
#include "brick_shape.h"
#include "gable_brick_shape.h"
#include "roof_shape.h"
#include "window_model.h"
#include "door_model.h"
#include <stdio.h>

Element::Element(Float3 pos)
    : m_removed(false)
    , m_pos(pos)
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

void Element::remove()
{
    m_removed = true;
}

void Element::unremove()
{
    m_removed = false;
}

bool Element::removed() const
{
    return m_removed;
}

Float3 Element::pos() const
{
    return m_pos;
}

int Element::orientation() const
{
    return 0;
}

int Element::width() const
{
    return 1;
}

BoundingBox Element::bounding_box() const
{
    BoundingBox bb;
    bb.vmin.v1 = m_pos.v1 - dimx / 2.0;
    bb.vmin.v2 = m_pos.v2 * dimh - dimh / 2.0;
    bb.vmin.v3 = m_pos.v3 - dimx / 2.0;
    bb.vmax.v1 = m_pos.v1 + dimx / 2.0;
    bb.vmax.v2 = m_pos.v2 * dimh + dimh / 2.0;
    bb.vmax.v3 = m_pos.v3 + dimx / 2.0;
    return bb;
}

int Element::kind() const
{
    return ELEMENT_HALF_BRICK;
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
            v_ufl.v2 = v_lfl.v2 + dimb * dimh;
            v_ufr.v2 = v_lfr.v2 + dimb * dimh;
        };
        if (orientation == 1) {
           v_ufr.v2 = v_lfr.v2 + dimb * dimh;
           v_ubr.v2 = v_lbr.v2 + dimb * dimh;
        };
        if (orientation == 2) {
            v_ubl.v2 = v_lbl.v2 + dimb * dimh;
            v_ubr.v2 = v_lbr.v2 + dimb * dimh;
        };
        if (orientation == 3) {
            v_ubl.v2 = v_lbl.v2 + dimb * dimh;
            v_ufl.v2 = v_lfl.v2 + dimb * dimh;
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

Face Element::gen_roof_face(int ix, float xf, float yf, float zf, int orientation) const
{
    Face f;

    float oh = 0.25;
    float t = RoofElement::dimt;
    Float3 v_lbl;
    Float3 v_lfl;
    Float3 v_lfr;
    Float3 v_lbr;
    Float3 v_ubl;
    Float3 v_ufl;
    Float3 v_ufr;
    Float3 v_ubr;
    if (orientation == 0) {
        v_lbl = face_vertex(-xf - oh, yf, -zf);
        v_lfl = face_vertex(-xf - oh, -yf - oh, zf + oh);
        v_lfr = face_vertex(xf + oh, -yf - oh, zf + oh);
        v_lbr = face_vertex(xf + oh, yf, -zf);
        v_ubl = face_vertex(-xf - oh, yf + t, -zf);
        v_ufl = face_vertex(-xf - oh, -yf - oh + t, zf + oh);
        v_ufr = face_vertex(xf + oh, -yf - oh + t, zf + oh);
        v_ubr = face_vertex(xf + oh, yf + t, -zf);
    } else if (orientation == 1) {
        v_lbl = face_vertex(-xf, yf, -zf - oh);
        v_lfl = face_vertex(-xf, yf, zf + oh);
        v_lfr = face_vertex(xf + oh, -yf - oh, zf + oh);
        v_lbr = face_vertex(xf + oh, -yf -oh, -zf - oh);
        v_ubl = face_vertex(-xf, yf + t, -zf - oh);
        v_ufl = face_vertex(-xf, yf + t, zf + oh);
        v_ufr = face_vertex(xf + oh, -yf - oh + t, zf + oh);
        v_ubr = face_vertex(xf + oh, -yf - oh + t, -zf - oh);
    } else if (orientation == 2) {
        v_lbl = face_vertex(-xf - oh, -yf - oh, -zf - oh);
        v_lfl = face_vertex(-xf - oh, yf, zf);
        v_lfr = face_vertex(xf + oh, yf, zf);
        v_lbr = face_vertex(xf + oh, -yf - oh, -zf - oh);
        v_ubl = face_vertex(-xf - oh, -yf - oh + t, -zf - oh);
        v_ufl = face_vertex(-xf - oh, yf + t, zf);
        v_ufr = face_vertex(xf + oh, yf + t, zf);
        v_ubr = face_vertex(xf + oh, -yf -oh + t, -zf - oh);
    } else {  // orientation = 3

        v_lbl = face_vertex(-xf - oh, -yf - oh, -zf - oh);
        v_lfl = face_vertex(-xf - oh, -yf - oh, zf + oh);
        v_lfr = face_vertex(xf, yf, zf + oh);
        v_lbr = face_vertex(xf, yf, -zf - oh);
        v_ubl = face_vertex(-xf - oh, -yf - oh + t, -zf - oh);
        v_ufl = face_vertex(-xf - oh, -yf - oh + t, zf + oh);
        v_ufr = face_vertex(xf, yf + t, zf + oh);
        v_ubr = face_vertex(xf, yf + t, -zf - oh);
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
PaintCan Element::roof_paint(0.0, 1.0, 0.0);
PaintCan Element::white_paint(1.0, 1.0, 1.0);
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

BoundingBox BrickElement::bounding_box() const
{
    BoundingBox bb;
    Float3 apos = pos();
    bb.vmin.v2 = apos.v2 * dimh - dimh / 2.0;
    bb.vmax.v2 = apos.v2 * dimh + dimh / 2.0;
    if (m_orientation == 0 || m_orientation == 2) {
        bb.vmin.v1 = apos.v1 - dimx;
        bb.vmin.v3 = apos.v3 - dimx / 2.0;
        bb.vmax.v1 = apos.v1 + dimx;
        bb.vmax.v3 = apos.v3 + dimx / 2.0;
    } else {
        bb.vmin.v1 = apos.v1 - dimx / 2.0;
        bb.vmin.v3 = apos.v3 - dimx;
        bb.vmax.v1 = apos.v1 + dimx / 2.0;
        bb.vmax.v3 = apos.v3 + dimx;
    }
    return bb;
}

int BrickElement::width() const
{
    return 2;
}

int BrickElement::kind() const
{
    return ELEMENT_BRICK;
}

GableBrickElement::GableBrickElement(float xpos, float ypos, float zpos, int orientation)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
{

}

const CadModel& GableBrickElement::model() const
{
    if (m_orientation == 1)
        return m_model_qns;
    if (m_orientation == 2)
        return m_model_qew;
    if (m_orientation == 3)
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

int GableBrickElement::width() const
{
    return 1;
}

int GableBrickElement::kind() const
{
    return ELEMENT_GABLE_BRICK;
}

DoorElement::DoorElement(float xpos, float ypos, float zpos, int orientation,
                             int width, int height, int hgrilles, int vgrilles)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
    , m_width(width)
    , m_height(height)
    , m_hgrilles(hgrilles)
    , m_vgrilles(vgrilles)
    , m_model(DoorModel(width, height * dimh, 1.0, dimb, vgrilles, hgrilles, 0.0))
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
    return pos().v2 + m_height / 2.0;
}

float DoorElement::bottom_level() const
{
    return pos().v2 - m_height / 2.0;
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

BoundingBox DoorElement::bounding_box() const
{
    BoundingBox bb;
    Float3 apos = pos();
    bb.vmin.v2 = apos.v2 *dimh - m_height * dimh / 2.0;
    bb.vmax.v2 = apos.v2 *dimh + m_height * dimh / 2.0;
    if (m_orientation == 0 || m_orientation == 2) {
        bb.vmin.v1 = apos.v1 - m_width / 2.0;
        bb.vmin.v3 = apos.v3 - dimx / 2.0;
        bb.vmax.v1 = apos.v1 + m_width / 2.0;
        bb.vmax.v3 = apos.v3 + dimx / 2.0;
    } else {
        bb.vmin.v1 = apos.v1 - dimx / 2.0;
        bb.vmin.v3 = apos.v3 - m_width / 2.0;
        bb.vmax.v1 = apos.v1 + dimx / 2.0;
        bb.vmax.v3 = apos.v3 + m_width / 2.0;
    }
    return bb;
}

int DoorElement::width() const
{
    return m_width;
}

int DoorElement::kind() const
{
    return ELEMENT_DOOR;
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
    return pos().v2 + m_height / 2.0;
}

float WindowElement::bottom_level() const
{
    return pos().v2 - m_height / 2.0;
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

BoundingBox WindowElement::bounding_box() const
{
    BoundingBox bb;
    Float3 apos = pos();
    bb.vmin.v2 = apos.v2 * dimh - m_height * dimh / 2.0;
    bb.vmax.v2 = apos.v2 * dimh + m_height * dimh / 2.0;
    if (m_orientation == 0 || m_orientation == 2) {
        bb.vmin.v1 = apos.v1 - m_width / 2.0;
        bb.vmin.v3 = apos.v3 - dimx / 2.0;
        bb.vmax.v1 = apos.v1 + m_width / 2.0;
        bb.vmax.v3 = apos.v3 + dimx / 2.0;
    } else {
        bb.vmin.v1 = apos.v1 - dimx / 2.0;
        bb.vmin.v3 = apos.v3 - m_width / 2.0;
        bb.vmax.v1 = apos.v1 + dimx / 2.0;
        bb.vmax.v3 = apos.v3 + m_width / 2.0;
    }
    return bb;
}

int WindowElement::width() const
{
    return m_width;
}

int WindowElement::kind() const
{
    return ELEMENT_WINDOW;
}

RoofElement::RoofElement(float xpos, float ypos, float zpos, int orientation, int width)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
    , m_width(width)
{
    CadModel rm(RoofShape(dimx, dimx, dimx, dimb, dimt), roof_paint, 0.0);
    for (int i = 0; i < width; i++) {
        float hw = 0.5 * (float) width;
        m_model.add(rm, 0.5 - hw + (float) i);
    }
    if (orientation == 1)
        m_model.rotate_ay(90.0);
    else if (orientation == 2)
        m_model.rotate_ay(180.0);
    else if (orientation == 3)
        m_model.rotate_ay(270.0);
}

void RoofElement::save_to_file(QDataStream& ds) const
{
    QString msg = "Roof(";
    ds.writeRawData(msg.toLatin1().data(), msg.length());
    Element::save_to_file(ds);
    msg = QString(", %1, %2)\n").arg(m_orientation).arg(m_width);
    ds.writeRawData(msg.toLatin1().data(), msg.length());
}

const CadModel& RoofElement::model() const
{
    return m_model;
}

float RoofElement::top_level() const
{
    return pos().v2 + 1.0;
}

Face RoofElement::face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_roof_face(ix, xf, yf, zf, m_orientation);
}

int RoofElement::sub_face_count() const
{
    return m_width;
}

Face RoofElement::top_sub_face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    float xoff = (m_orientation == 0 || m_orientation == 2) ? (float) ix : 0.0;
    float zoff = (m_orientation == 0 || m_orientation == 2) ? 0.0 : (float) ix;
    return gen_top_sub_face(xf, yf, zf, xoff, zoff);
}

bool RoofElement::contains(Float3 pos) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_contains(pos, xf, yf, zf);
}

int RoofElement::orientation() const
{
    return m_orientation;
}

BoundingBox RoofElement::bounding_box() const
{
    BoundingBox bb;
    Float3 apos = pos();
    float q = dimx / 4;
    bb.vmin.v2 = apos.v2 * dimh - dimh / 2.0 - q * dimh;
    bb.vmax.v2 = apos.v2 * dimh + dimh / 2.0 + 2.0 * dimt;
    if (m_orientation == 0) {
        bb.vmin.v1 = apos.v1 - m_width / 2.0 - q;
        bb.vmin.v3 = apos.v3 - dimx / 2.0;
        bb.vmax.v1 = apos.v1 + m_width / 2.0 + q;
        bb.vmax.v3 = apos.v3 + dimx / 2.0 + q;
    } else if (m_orientation == 2) {
        bb.vmin.v1 = apos.v1 - m_width / 2.0 - q;
        bb.vmin.v3 = apos.v3 - dimx / 2.0 - q;
        bb.vmax.v1 = apos.v1 + m_width / 2.0 + q;
        bb.vmax.v3 = apos.v3 + dimx / 2.0;
    } else if (m_orientation == 1) {
        bb.vmin.v1 = apos.v1 - dimx / 2.0;
        bb.vmin.v3 = apos.v3 - m_width / 2.0 - q;
        bb.vmax.v1 = apos.v1 + dimx / 2.0 + q;
        bb.vmax.v3 = apos.v3 + m_width / 2.0 + q;
    } else {
        bb.vmin.v1 = apos.v1 - dimx / 2.0 - q;
        bb.vmin.v3 = apos.v3 - m_width / 2.0 - q;
        bb.vmax.v1 = apos.v1 + dimx / 2.0;
        bb.vmax.v3 = apos.v3 + m_width / 2.0 + q;
    }
    return bb;
}

int RoofElement::width() const
{
    return m_width;
}

int RoofElement::kind() const
{
    return ELEMENT_ROOF;
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

const CadModel& LedgeElement::model() const
{
    return m_model;
}

Face LedgeElement::face(int ix) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_face(ix, xf, yf, zf);
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
    return gen_top_sub_face(xf, yf, zf, xoff, zoff);
}

bool LedgeElement::contains(Float3 pos) const
{
    float xf = (m_orientation == 0 || m_orientation == 2) ? m_width / 2.0 : 0.5;
    float yf = 0.5;
    float zf = (m_orientation == 0 || m_orientation == 2) ? 0.5 : m_width / 2.0;
    return gen_contains(pos, xf, yf, zf);
}

int LedgeElement::orientation() const
{
    return m_orientation;
}

BoundingBox LedgeElement::bounding_box() const
{
    BoundingBox bb;
    Float3 apos = pos();
    bb.vmin.v2 = apos.v2 * dimh - dimh / 2.0;
    bb.vmax.v2 = apos.v2 * dimh + dimh / 2.0;
    if (m_orientation == 0 || m_orientation == 2) {
        bb.vmin.v1 = apos.v1 - m_width / 2.0;
        bb.vmin.v3 = apos.v3 - dimx / 2.0;
        bb.vmax.v1 = apos.v1 + m_width / 2.0;
        bb.vmax.v3 = apos.v3 + dimx / 2.0;
    } else {
        bb.vmin.v1 = apos.v1 - dimx / 2.0;
        bb.vmin.v3 = apos.v3 - m_width / 2.0;
        bb.vmax.v1 = apos.v1 + dimx / 2.0;
        bb.vmax.v3 = apos.v3 + m_width / 2.0;
    }
    return bb;
}

int LedgeElement::width() const
{
    return m_width;
}

int LedgeElement::kind() const
{
    return ELEMENT_LEDGE;
}

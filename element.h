
#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "float3.h"
#include "face.h"
#include "brick_shape.h"
#include "paint_can.h"
#include "cad_model.h"
#include <QFile>
#include <QDataStream>

#define NORTH 0
#define WEST  1
#define SOUTH 2
#define EAST  3

#define BOTTOM_FACE 0
#define TOP_FACE    1
#define LEFT_FACE   2
#define RIGHT_FACE  3
#define FRONT_FACE  4
#define BACK_FACE   5

class Element
{
public:
    static constexpr float dimh = 2.0 / 3.0;
    static constexpr float dimb = 0.025;
    static PaintCan red_paint;
    static PaintCan white_paint;
    static PaintCan door_paint;
    static PaintCan gray_paint;
    Element(Float3 pos);
    Element() = delete;
    virtual ~Element();
    Float3 get_pos() const;
    virtual void save_to_file(QDataStream& ds) const;
    virtual const CadModel& model() const;
    virtual float top_level() const;
    virtual Face face(int ix) const;
    virtual int sub_face_count() const;
    virtual Face top_sub_face(int ix) const;
    virtual bool contains(Float3 pos) const;
    Face gen_face(int ix, float xf, float yf, float zf) const;
    Face gen_top_sub_face(float xf, float yf, float zf, float xoff, float zoff) const;
    bool gen_contains(Float3 pos, float xf, float yf, float zf) const;
protected:
    Float3 face_vertex(float xf, float yf, float zf) const;
private:
    Float3 m_pos;
    static CadModel m_default_model;
};

class HalfBrickElement: public Element
{
public:
    HalfBrickElement(float xpos, float ypos, float zpos);
    HalfBrickElement() = delete;
    void save_to_file(QDataStream& ds) const override;
};

class BrickElement: public Element
{
public:
    BrickElement(float xpos, float ypos, float zpos, int orientation);
    BrickElement() = delete;
    void save_to_file(QDataStream& ds) const override;
    const CadModel& model() const override;
    Face face(int ix) const override;
    int sub_face_count() const override;
    Face top_sub_face(int ix) const override;
    bool contains(Float3 pos) const override;

private:
    int m_orientation;
    static CadModel m_model_ns;
    static CadModel m_model_ew;
};

class DoorElement: public Element
{
public:
    DoorElement(float xpos, float ypos, float zpos, int orientation,
                  int width, int height, int hgrilles, int vgrilles);
    DoorElement() = delete;
    void save_to_file(QDataStream& ds) const override;
    const CadModel& model() const override;
    float top_level() const override;
    Face face(int ix) const override;
    int sub_face_count() const override;
    Face top_sub_face(int ix) const override;
    bool contains(Float3 pos) const override;

private:
    int m_orientation;
    int m_width;
    int m_height;
    int m_hgrilles;
    int m_vgrilles;
    CadModel m_model;
};


class WindowElement: public Element
{
public:
    WindowElement(float xpos, float ypos, float zpos, int orientation,
                  int width, int height, int hgrilles, int vgrilles);
    WindowElement() = delete;
    void save_to_file(QDataStream& ds) const override;
    const CadModel& model() const override;
    float top_level() const override;
    Face face(int ix) const override;
    int sub_face_count() const override;
    Face top_sub_face(int ix) const override;
    bool contains(Float3 pos) const override;

private:
    int m_orientation;
    int m_width;
    int m_height;
    int m_hgrilles;
    int m_vgrilles;
    CadModel m_model;
};

class LedgeElement: public Element
{
public:
    LedgeElement(float xpos, float ypos, float zpos, int orientation, int width);
    LedgeElement() = delete;
    void save_to_file(QDataStream& ds) const override;
    const CadModel& model() const override;
    Face face(int ix) const override;
    int sub_face_count() const override;
    Face top_sub_face(int ix) const override;
    bool contains(Float3 pos) const override;

private:
    int m_orientation;
    int m_width;
    CadModel m_model;
};

#endif // _ELEMENT_H_

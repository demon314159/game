
#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_

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

class Element
{
public:
    static constexpr float dimh = 2.0 / 3.0;
    static constexpr float dimb = 0.025;
    static PaintCan red_paint;
    static PaintCan white_paint;
    static PaintCan gray_paint;
    Element(float3 pos);
    Element() = delete;
    virtual ~Element();
    float3 get_pos() const;
    virtual void save_to_file(QDataStream& ds) const;
    virtual CadModel& model();
    virtual float top_level() const;
    virtual Face top_face() const;
    virtual int sub_face_count() const;
    virtual Face top_sub_face(int ix) const;
    virtual bool contains(float3 pos) const;
    Face gen_face(float xf, float yf, float zf) const;
    Face gen_sub_face(float xf, float yf, float zf, float xoff, float zoff) const;
    bool gen_contains(float3 pos, float xf, float yf, float zf) const;

private:
    float3 m_pos;
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
    CadModel& model() override;
    Face top_face() const override;
    int sub_face_count() const override;
    Face top_sub_face(int ix) const override;
    bool contains(float3 pos) const override;

private:
    int m_orientation;
    static CadModel m_model_ns;
    static CadModel m_model_ew;
};

class WindowElement: public Element
{
public:
    WindowElement(float xpos, float ypos, float zpos, int orientation,
                  int width, int height, int hgrilles, int vgrilles);
    WindowElement() = delete;
    void save_to_file(QDataStream& ds) const override;
    CadModel& model() override;
    float top_level() const override;
    Face top_face() const override;
    int sub_face_count() const override;
    Face top_sub_face(int ix) const override;
    bool contains(float3 pos) const override;

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
    CadModel& model() override;
    Face top_face() const override;
    int sub_face_count() const override;
    Face top_sub_face(int ix) const override;
    bool contains(float3 pos) const override;

private:
    int m_orientation;
    int m_width;
    CadModel m_model;
};

#endif // _ELEMENTS_H_


#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_

#include "float3.h"
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
    const float dimw = 1.0;
    const float dimh = 2.0 / 3.0;
    const float dimb = 0.025;
    const PaintCan red_paint = PaintCan(1.0, 0.0, 0.0);
    const PaintCan white_paint = PaintCan(1.0, 1.0, 1.0);
    Element(float3 pos);
    Element() = delete;
    virtual ~Element();
    virtual void save_to_file(QDataStream& ds) const;
    float3 get_pos() const;
    virtual CadModel& get_model();

private:
    float3 m_pos;
    CadModel m_default_model = CadModel(BrickShape(dimw, dimh, dimw, dimb), red_paint, 0.0);
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
    CadModel& get_model() override;

private:
    int m_orientation;
    CadModel m_model_ns = CadModel(BrickShape(2.0 * dimw, dimh, dimw, dimb), red_paint, 0.0);
    CadModel m_model_ew = CadModel(BrickShape(dimw, dimh, 2.0 * dimw, dimb), red_paint, 0.0);
};

class WindowElement: public Element
{
public:
    WindowElement(float xpos, float ypos, float zpos, int orientation,
                  int width, int height, int hgrilles, int vgrilles);
    WindowElement() = delete;
    void save_to_file(QDataStream& ds) const override;
    CadModel& get_model() override;

private:
    int m_orientation;
    int m_width;
    int m_height;
    int m_hgrilles;
    int m_vgrilles;
    CadModel m_model;
};

#endif // _ELEMENTS_H_


#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_

#include "float3.h"
#include <QFile>
#include <QDataStream>

#define NORTH 0
#define WEST  1
#define SOUTH 2
#define EAST  3

class Element
{
public:
    Element(float3 pos);
    Element() = delete;
    virtual ~Element();
    virtual void save_to_file(QDataStream& ds) const;

private:
    float3 m_pos;
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
private:
    int m_orientation;
};

class WindowElement: public Element
{
public:
    WindowElement(float xpos, float ypos, float zpos, int orientation,
                  int width, int height, int hgrilles, int vgrilles);
    WindowElement() = delete;
    void save_to_file(QDataStream& ds) const override;
private:
    int m_orientation;
    float m_width;
    float m_height;
    int m_hgrilles;
    int m_vgrilles;
};

#endif // _ELEMENTS_H_

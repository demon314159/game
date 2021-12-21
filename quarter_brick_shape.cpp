
#include "quarter_brick_shape.h"

QuarterBrickShape::QuarterBrickShape(float dimx, float dimy, float dimz, float dimb)
    : BrickShape(dimx, dimy, dimz, dimb)
{
}

QuarterBrickShape::~QuarterBrickShape()
{
}

void QuarterBrickShape::define_shape()
{
    // faces
    add_face(0x44, 0x54, 0x74, 0x64, true);
    add_face(0x02, 0x12, 0x52, 0x42, true);
    add_face(0x04, 0x14, 0x72, 0x62);
    add_face(0x01, 0x41, 0x61, true);
    add_face(0x11, 0x51, 0x71);

    // one bevel for left face
    add_face(0x04, 0x14, 0x12, 0x02, true);

    // four bevels for right face
    add_face(0x44, 0x54, 0x52, 0x42);
    add_face(0x54, 0x74, 0x71, 0x51);
    add_face(0x74, 0x64, 0x62, 0x72);
    add_face(0x64, 0x44, 0x41, 0x61);
    // four missing bevels
    add_face(0x01, 0x41, 0x42, 0x02);
    add_face(0x01, 0x61, 0x62, 0x04, true);
    add_face(0x11, 0x51, 0x52, 0x12, true);
    add_face(0x11, 0x71, 0x72, 0x14);

    // 6 remaining triangles
    add_face(0x01, 0x02, 0x04);
    add_face(0x11, 0x12, 0x14, true);
    add_face(0x41, 0x42, 0x44, true);
    add_face(0x51, 0x52, 0x54);
    add_face(0x61, 0x62, 0x64);
    add_face(0x71, 0x72, 0x74, true);
}



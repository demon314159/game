#include <cmath>
#include "car.h"
#include "track_style.h"
#include "box_shape.h"
#include "ring_shape.h"
#include "cylinder_shape.h"

#define ANI_ID_CAR 2.0

Car::Car()
    : m_speed(7.5)
    , m_section(0)
    , m_lane(0)
    , m_distance(0.0)
    , m_angle(0.0)
    , m_position({0.0, 0.0, 0.0})
{
}

Car::~Car()
{
}

void Car::advance(int nanoseconds, Section** section, int sections)
{
//    float turns_per_second = 5.0 / 20.0;
//    m_angle += ((360.0 * turns_per_second / 1000000000.0) * (double) nanoseconds);
//
// Just handle positive speed for now
//
    m_distance += ((m_speed / 1000000000.0) * (double) nanoseconds);
    double slack = section[m_section]->total_distance(m_lane) - m_distance;
    if (slack <= 0.0) {
        m_section = ((m_section + 1) == sections) ? 0 :  m_section + 1;
        m_distance = -slack;
    }
    m_position = section[m_section]->car_position(m_lane, m_distance);
    m_angle = section[m_section]->car_angle(m_lane, m_distance);

//    printf("Car::advance(%d ns, %d sections):  distance = %5.1lf\n", nanoseconds, sections, m_distance);
//    printf("  angle = %5.1lf,  pos = (%5.1lf, %5.1lf, %5.1lf}\n", m_angle, m_position.v1, m_position.v2, m_position.v3);
}

double Car::angle() const
{
    return m_angle - 90.0;
}

Double3 Car::position() const
{
    return m_position;
}

CadModel Car::cad_model() const
{
    CadModel vehicle;
    build_wheels(&vehicle);
    build_car(&vehicle);
    return vehicle;
}

void Car::build_car(CadModel* vehicle) const
{
    float th = TrackStyle::track_height;
    float F = 2.16;
    float H = 0.2;
    float hb = 0.1 + th;
    float dz1 = (1.0 / 3.0) / 2.0; // width / 2
    float dz = (1.0 / 2.0) / 2.0; // width / 2
    float px0 = 0.0;
    float py0 = hb + 0.15 * H;
    float px1 = 0.439 * F + px0;
    float py1 = hb + 1.0 * H;
    float px2 = 0.122 * F + px1;
    float py2 = hb + 1.0 * H;
    float px3 = 0.05 * F + px2;
    float py3 = hb + 1.75 * H;
    float px4 = 0.122 * F + px3;
    float py4 = hb + 1.75 * H;
    float px5 = 0.195 * F + px4;
    float py5 = hb + 1.0 * H;
    float px6 = 0.098 * F + px5;
    float py6 = hb + 1.0 * H;

    float xc = (px0 + px6) / 2.0;

    PaintCan body_p(1.0, 0.25, 0.5);
    CadModel body1 = CadModel(BoxShape({px0 - xc, hb, -dz1}, {px0 - xc, hb, dz1}, {px1 - xc, hb, dz}, {px1 - xc, hb, -dz},
                                       {px0 - xc, py0, -dz1}, {px0 - xc, py0, dz1}, {px1 - xc, py1, dz}, {px1 - xc, py1, -dz}), body_p, ANI_ID_CAR);
    CadModel body2 = CadModel(BoxShape({px1 - xc, hb, -dz}, {px1 - xc, hb, dz}, {px2 - xc, hb, dz}, {px2 - xc, hb, -dz},
                                       {px1 - xc, py1, -dz}, {px1 - xc, py1, dz}, {px2 - xc, py2, dz}, {px2 - xc, py2, -dz}), body_p, ANI_ID_CAR);
    CadModel body3 = CadModel(BoxShape({px2 - xc, hb, -dz}, {px2 - xc, hb, dz}, {px3 - xc, hb, dz}, {px3 - xc, hb, -dz},
                                       {px2 - xc, py2, -dz}, {px2 - xc, py2, dz}, {px3 - xc, py3, dz}, {px3 - xc, py3, -dz}), body_p, ANI_ID_CAR);
    CadModel body4 = CadModel(BoxShape({px3 - xc, hb, -dz}, {px3 - xc, hb, dz}, {px4 - xc, hb, dz}, {px4 - xc, hb, -dz},
                                       {px3 - xc, py3, -dz}, {px3 - xc, py3, dz}, {px4 - xc, py4, dz}, {px4 - xc, py4, -dz}), body_p, ANI_ID_CAR);
    CadModel body5 = CadModel(BoxShape({px4 - xc, hb, -dz}, {px4 - xc, hb, dz}, {px5 - xc, hb, dz}, {px5 - xc, hb, -dz},
                                       {px4 - xc, py4, -dz}, {px4 - xc, py4, dz}, {px5 - xc, py5, dz}, {px5 - xc, py5, -dz}), body_p, ANI_ID_CAR);
    CadModel body6 = CadModel(BoxShape({px5 - xc, hb, -dz}, {px5 - xc, hb, dz}, {px6 - xc, hb, dz}, {px6 - xc, hb, -dz},
                                       {px5 - xc, py5, -dz}, {px5 - xc, py5, dz}, {px6 - xc, py6, dz}, {px6 - xc, py6, -dz}), body_p, ANI_ID_CAR);

    vehicle->add(body1, 0.0, 0.0, 0.0);
    vehicle->add(body2, 0.0, 0.0, 0.0);
    vehicle->add(body3, 0.0, 0.0, 0.0);
    vehicle->add(body4, 0.0, 0.0, 0.0);
    vehicle->add(body5, 0.0, 0.0, 0.0);
    vehicle->add(body6, 0.0, 0.0, 0.0);
}

CadModel Car::build_wheel(float r_tire, float r_rim, float r_inner, float r_spacer, float width) const
{
    float bevel = width / 10.0;
    PaintCan tire_p(1.0, 0.0, 0.0);
    PaintCan rim_p(0.75, 0.75, 0.75);
    PaintCan hub_p(1.0, 0.922, 0.0);
    PaintCan knob_p(0.25, 0.25, 0.25);
    CadModel tire = CadModel(RingShape(r_tire, r_rim, width, bevel, 0.0, bevel, 0.0), tire_p, ANI_ID_CAR);
    bevel = (r_rim - r_inner) / 5.0;
    CadModel rim = CadModel(RingShape(r_rim, r_inner, width, 0.0, bevel, 0.0, bevel), rim_p, ANI_ID_CAR);
    CadModel spacer = CadModel(RingShape(r_inner, r_spacer, width * 0.9), rim_p, ANI_ID_CAR);
    CadModel hub = CadModel(CylinderShape(r_spacer, width * 0.2), hub_p, ANI_ID_CAR);
    CadModel knob = CadModel(CylinderShape(r_rim * 0.25, width * 0.3, r_rim * 0.25 * 0.2, r_rim * 0.25 * 0.2), knob_p, ANI_ID_CAR);
    tire.add(rim, 0.0, 0.0, 0.0);
    tire.add(spacer, 0.0, 0.0, 0.0);
    tire.add(hub, 0.0, 0.0, 0.0);
    tire.add(knob, 0.0, 0.0, 0.0);
    return tire;
}

void Car::build_wheels(CadModel* vehicle) const
{
    float car_width = TrackStyle::car_width;
    float th = TrackStyle::track_height;
//    float ofs = TrackStyle::car_gap / 2.0 + TrackStyle::car_width / 2.0;
    float ofs = 0.0;
    float xofs = 0.0;
//    float xofs = 2.16 / 2.0;
    float spacing_b = car_width * 0.825;
//    float spacing_f = car_width * 0.775;
    float spacing_f = car_width * 0.675;
    float axle_spacing = car_width * 1.25;
    float back_radius = car_width * 0.1875;
    float front_radius = car_width * 0.16875;
    float rim_radius = car_width * 0.1125;
    float inner_radius = car_width * 0.1;
    float spacer_radius = car_width * 0.09;

    CadModel back_wheel = build_wheel(back_radius, rim_radius, inner_radius, spacer_radius, car_width * 0.2);
    CadModel front_wheel = build_wheel(front_radius, rim_radius, inner_radius, spacer_radius, car_width * 0.1375);
    PaintCan axle_p(0.75, 0.75, 0.75);
    CadModel front_axle = CadModel(CylinderShape(rim_radius * 0.25 * 0.5, spacing_f), axle_p, ANI_ID_CAR);
    CadModel back_axle = CadModel(CylinderShape(rim_radius * 0.25 * 0.5, spacing_b), axle_p, ANI_ID_CAR);

    vehicle->add(back_wheel, axle_spacing / 2.0 + xofs, -spacing_b / 2.0 + ofs, back_radius + th);
    vehicle->add(back_wheel, axle_spacing / 2.0 + xofs, spacing_b / 2.0 + ofs, back_radius + th);
    vehicle->add(front_wheel, -axle_spacing / 2.0 + xofs, -spacing_f / 2.0 + ofs, front_radius + th);
    vehicle->add(front_wheel, -axle_spacing / 2.0 + xofs, spacing_f / 2.0 + ofs, front_radius + th);
    vehicle->add(front_axle, -axle_spacing / 2.0 + xofs, 0.0, front_radius + th);
    vehicle->add(back_axle, axle_spacing / 2.0 + xofs, 0.0, back_radius + th);
    vehicle->rotate_ax(-90.0);
}




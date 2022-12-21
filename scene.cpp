//
// scene.cpp
//
#include "scene.h"

Scene::Scene(const PuzzleBook* puzzle_book, const ShapeSet* shape_set)
    : m_puzzle_book(puzzle_book)
    , m_shape_set(shape_set)
    , m_lb_pressed(false)
    , m_lb_x(0)
    , m_lb_y(0)
    , m_docks(0)
{
}

Scene::~Scene()
{
}

void Scene::determine_layout(QPainter& painter)
{
    int vx = painter.viewport().left();
    int vy = painter.viewport().top();
    int vw = painter.viewport().width();
    int vh = painter.viewport().height();
    int xgy = (vh * 4) / 3;
    int ygx = (vw * 3) / 4;
    if (xgy <= vw) {
        m_xbase = vx + (vw - xgy) / 2;
        m_ybase = vy;
        m_unit = vh / VERT_UNITS;
    } else {
        m_xbase = vx;
        m_ybase = vy + (vh - ygx) / 2;
        m_unit = vw / HORZ_UNITS;
    }
    m_scx = vx + vw / 2;
    m_scy = vy + vh / 2;
}

QRect Scene::rack_rect() const
{
    int dimh = m_puzzle_book->dimh();
    int dimv = m_puzzle_book->dimv();
    int w = dimh * m_unit;
    int h = dimv * m_unit;
    int x1 = m_scx - w / 2;
    int y1 = m_scy - h / 2;
    return QRect(x1, y1, w, h);
}

QRect Scene::dock_rect(int dock_ix) const
{
    switch(dock_ix) {
        case 1:
            return QRect(m_xbase + 12 * m_unit, m_ybase + 0 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 2:
            return QRect(m_xbase + 6 * m_unit, m_ybase + 12 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 3:
            return QRect(m_xbase + 12 * m_unit, m_ybase + 12 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 4:
            return QRect(m_xbase + 0 * m_unit, m_ybase + 6 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 5:
            return QRect(m_xbase + 18 * m_unit, m_ybase + 6 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 6:
            return QRect(m_xbase + 0 * m_unit, m_ybase + 0 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 7:
            return QRect(m_xbase + 18 * m_unit, m_ybase + 0 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 8:
            return QRect(m_xbase + 0 * m_unit, m_ybase + 12 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 9:
            return QRect(m_xbase + 18 * m_unit, m_ybase + 12 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        default: // and case 0
            return QRect(m_xbase + 6 * m_unit, m_ybase + 0 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
    }
}

void Scene::draw(QPainter& painter)
{
    determine_layout(painter);
    map_docks();
    draw_rack(painter);
    draw_pieces(painter);
    draw_cursor(painter);
}

void Scene::draw_rack(QPainter& painter)
{
    const PuzzleBook* pb = m_puzzle_book;
    QPen inside_pen(Qt::darkRed);
    QPen outside_pen(Qt::black);
    outside_pen.setWidth(3);
    painter.fillRect(rack_rect(), Qt::red);
    painter.setPen(outside_pen);
    painter.drawRect(rack_rect());
    painter.setPen(inside_pen);
    for (int i = 1; i < pb->dimh(); i++) {
        painter.drawLine(rack_rect().left() + m_unit * i, rack_rect().top(), rack_rect().left() + m_unit * i, rack_rect().bottom());
    }
    for (int i = 1; i < pb->dimv(); i++) {
        painter.drawLine(rack_rect().left(), rack_rect().top() + m_unit * i, rack_rect().right(), rack_rect().top() + m_unit * i);
    }
}

void Scene::draw_pieces(QPainter& painter)
{
    const PuzzleBook* pb = m_puzzle_book;
    for (int i = 0; i < m_docks; i++) {
        int pix = m_dock_list[i];
        if (m_puzzle_book->on_board(pix)) {
            draw_on_board_shape(painter, rack_rect(), pb->shape_id(pix), pb->orientation(pix), pb->posh(pix), pb->posv(pix));
        } else {
            draw_off_board_shape(painter, dock_rect(i), pb->shape_id(pix), pb->orientation(pix));
        }
    }
}

void Scene::draw_cursor(QPainter& painter)
{
    if (m_lb_pressed) {
        QPen inside_pen(Qt::blue);
        painter.setPen(inside_pen);

        painter.drawRect(QRect(m_lb_x - m_unit / 2, m_lb_y - m_unit / 2, m_unit, m_unit));

    }
}

void Scene::draw_tile(QPainter& painter, int sx, int sy, int shape_id, int orientation, int tposh, int tposv)
{
    QBrush brush(Qt::yellow);
    QPen inside_pen(Qt::darkYellow);
    QPen outside_pen(Qt::black);
    outside_pen.setWidth(3);
    painter.fillRect(QRect(sx, sy, m_unit, m_unit), brush);
    painter.setPen(m_shape_set->tile_at(shape_id, orientation, tposh, tposv + 1) ? inside_pen : outside_pen);
    painter.drawLine(sx, sy, sx + m_unit, sy);
    painter.setPen(m_shape_set->tile_at(shape_id, orientation, tposh + 1, tposv) ? inside_pen : outside_pen);
    painter.drawLine(sx + m_unit, sy, sx + m_unit, sy + m_unit);
    painter.setPen(m_shape_set->tile_at(shape_id, orientation, tposh, tposv - 1) ? inside_pen : outside_pen);
    painter.drawLine(sx + m_unit, sy + m_unit, sx, sy + m_unit);
    painter.setPen(m_shape_set->tile_at(shape_id, orientation, tposh - 1, tposv) ? inside_pen : outside_pen);
    painter.drawLine(sx, sy + m_unit, sx, sy);
}

void Scene::draw_on_board_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation, int posh, int posv)
{
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int tposh = m_shape_set->posh(shape_id, i, orientation);
        int tposv = m_shape_set->posv(shape_id, i, orientation);
        int x = rect.left() + (tposh + posh) * m_unit;
        int y = rect.bottom() - (tposv + posv) * m_unit - m_unit + 1;
        draw_tile(painter, x, y, shape_id, orientation, tposh, tposv);
    }
}

void Scene::draw_off_board_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation)
{
    int cx = m_shape_set->horz_center(shape_id, orientation, m_unit);
    int cy = m_shape_set->vert_center(shape_id, orientation, m_unit);
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int tposh = m_shape_set->posh(shape_id, i, orientation);
        int tposv = m_shape_set->posv(shape_id, i, orientation);
        int x = rect.center().x() + tposh * m_unit - cx;
        int y = rect.center().y() - tposv * m_unit + cy - m_unit / 2;
        draw_tile(painter, x, y, shape_id, orientation, tposh, tposv);
    }
}

void Scene::map_docks()
{
    m_docks = 0;
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (!m_puzzle_book->locked(i)) {
            m_dock_list[m_docks++] = i;
        }
    }
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (m_puzzle_book->locked(i)) {
            m_dock_list[m_docks++] = i;
        }
    }
}

void Scene::mouse_press(int mx, int my)
{
    m_lb_pressed = mouse_test_pieces(mx, my);
    m_lb_x = mx;
    m_lb_y = my;
}

void Scene::mouse_release(int mx, int my)
{
    m_lb_pressed = false;
    m_lb_x = mx;
    m_lb_y = my;
}

void Scene::mouse_move(int mx, int my)
{
    if (m_lb_pressed) {
        m_lb_x = mx;
        m_lb_y = my;
    }
}

bool Scene::mouse_test_pieces(int mx, int my) const
{
    const PuzzleBook* pb = m_puzzle_book;
    for (int i = 0; i < m_docks; i++) {
        int pix = m_dock_list[i];
        if (m_puzzle_book->on_board(pix)) {
            if (mouse_test_on_board_shape(mx, my, rack_rect(), pb->shape_id(pix), pb->orientation(pix), pb->posh(pix), pb->posv(pix))) {
                printf("Mouse hit om board dock %d, pix %d\n", i, pix);
                return true;
            }
        } else {
            if (mouse_test_off_board_shape(mx, my, dock_rect(i), pb->shape_id(pix), pb->orientation(pix))) {
                printf("Mouse hit off board dock %d, pix %d\n", i, pix);
                return true;
            }
        }
    }
    printf("no hits\n");
    return false;
}

bool Scene::mouse_test_on_board_shape(int mx, int my, const QRect& rect, int shape_id, int orientation, int posh, int posv) const
{
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int tposh = m_shape_set->posh(shape_id, i, orientation);
        int tposv = m_shape_set->posv(shape_id, i, orientation);
        int x = rect.left() + (tposh + posh) * m_unit;
        int y = rect.bottom() - (tposv + posv) * m_unit - m_unit + 1;
        if (mouse_test_tile(mx, my, x, y)) {
            printf("Mouse hit on tile %d\n", i);
            return true;
        }
    }
    return false;
}

bool Scene::mouse_test_off_board_shape(int mx, int my, const QRect& rect, int shape_id, int orientation) const
{
    int cx = m_shape_set->horz_center(shape_id, orientation, m_unit);
    int cy = m_shape_set->vert_center(shape_id, orientation, m_unit);
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int tposh = m_shape_set->posh(shape_id, i, orientation);
        int tposv = m_shape_set->posv(shape_id, i, orientation);
        int x = rect.center().x() + tposh * m_unit - cx;
        int y = rect.center().y() - tposv * m_unit + cy - m_unit / 2;
        if (mouse_test_tile(mx, my, x, y)) {
            printf("Mouse hit on tile %d\n", i);
            return true;
        }
    }
    return false;
}

bool Scene::mouse_test_tile(int mx, int my, int sx, int sy) const
{
    return QRect(sx, sy, m_unit, m_unit).contains(mx, my);
}

//
// scene.cpp
//
#include "scene.h"

Scene::Scene(PuzzleBook* puzzle_book, const ShapeSet* shape_set)
    : m_puzzle_book(puzzle_book)
    , m_shape_set(shape_set)
    , m_left_down(false)
    , m_mouse_x(0)
    , m_mouse_y(0)
    , m_offset_x(0)
    , m_offset_y(0)
    , m_mouse_dock(0)
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
    float ux = (float) vw / ((float) HORZ_UNITS + 4.0 / (float) BORDER_F);
    float uy = (float) vh / ((float) VERT_UNITS + 3.0 / (float) BORDER_F);
    m_unit = std::min((int) ux, (int) uy);
    m_scx = vx + vw / 2;
    m_scy = vy + vh / 2;
    int ib = m_unit / BORDER_F;
    int ob = m_unit / (2 * BORDER_F);
    m_xbase = m_scx - (12 * m_unit + ob + ib + ib / 2);
    m_ybase = m_scy - (9 * m_unit + ob + ib);
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
    int ib = m_unit / BORDER_F;
    int ob = m_unit / (2 * BORDER_F);
    switch(dock_ix) {
        case 1:
            return QRect(m_xbase + 12 * m_unit + ob + 2 * ib, m_ybase + ob, 6 * m_unit - 1, 6 * m_unit - 1);
        case 2:
            return QRect(m_xbase + 6 * m_unit + ob + ib, m_ybase + 12 * m_unit + ob + 2 * ib, 6 * m_unit - 1, 6 * m_unit - 1);
        case 3:
            return QRect(m_xbase + 12 * m_unit + ob + 2 * ib, m_ybase + 12 * m_unit + ob + 2 * ib, 6 * m_unit - 1, 6 * m_unit - 1);
        case 4:
            return QRect(m_xbase + ob, m_ybase + 6 * m_unit + ob + ib, 6 * m_unit - 1, 6 * m_unit - 1);
        case 5:
            return QRect(m_xbase + 18 * m_unit + ob + 3 * ib, m_ybase + 6 * m_unit + ob + ib, 6 * m_unit - 1, 6 * m_unit - 1);
        case 6:
            return QRect(m_xbase + ob, m_ybase + ob, 6 * m_unit - 1, 6 * m_unit - 1);
        case 7:
            return QRect(m_xbase + 18 * m_unit + ob + 3 * ib, m_ybase + ob, 6 * m_unit - 1, 6 * m_unit - 1);
        case 8:
            return QRect(m_xbase + ob, m_ybase + 12 * m_unit + ob + 2 * ib, 6 * m_unit - 1, 6 * m_unit - 1);
        case 9:
            return QRect(m_xbase + 18 * m_unit + ob + 3 * ib, m_ybase + 12 * m_unit + ob + 2 * ib, 6 * m_unit - 1, 6 * m_unit - 1);
        default: // and case 0
            return QRect(m_xbase + 6 * m_unit + ob + ib, m_ybase + ob, 6 * m_unit - 1, 6 * m_unit - 1);
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

//    painter.fillRect(rack_rect(), QColor(223, 0, 0));
    painter.fillRect(rack_rect(), QColor(255, 63, 63));


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
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        int pix = m_dock_list[i];
        if (!(m_left_down && i == m_mouse_dock)) {
            if (m_puzzle_book->on_board(pix)) {
                draw_on_board_shape(painter, rack_rect(), pb->shape_id(pix), pb->orientation(pix), pb->posh(pix), pb->posv(pix));
            } else {
                draw_off_board_shape(painter, dock_rect(i), pb->shape_id(pix), pb->orientation(pix));
            }
        }
    }
}

void Scene::draw_cursor(QPainter& painter)
{
    if (m_left_down) {
        int pix = m_dock_list[m_mouse_dock];
        int shape_id = m_puzzle_book->shape_id(pix);
        int orientation = m_puzzle_book->orientation(pix);
        draw_shape(painter, shape_id, orientation, m_mouse_x + m_offset_x, m_mouse_y + m_offset_y);
        painter.setPen(Qt::black);
    }
}

void Scene::draw_tile(QPainter& painter, int sx, int sy, int shape_id, int orientation, int tposh, int tposv)
{
    QBrush brush(QColor(239, 239, 0));
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

void Scene::draw_shape(QPainter& painter, int shape_id, int orientation, int sx, int sy)
{
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int tposh = m_shape_set->posh(shape_id, i, orientation);
        int tposv = m_shape_set->posv(shape_id, i, orientation);
        int x = sx + tposh * m_unit;
        int y = sy - tposv * m_unit - m_unit + 1;
        draw_tile(painter, x, y, shape_id, orientation, tposh, tposv);
    }
}

int Scene::on_board_tile_pos_x(const QRect& rect, int posh, int tposh) const
{
    return rect.left() + (tposh + posh) * m_unit;
}

int Scene::on_board_tile_pos_y(const QRect& rect, int posv, int tposv) const
{
    return rect.bottom() - (tposv + posv) * m_unit - m_unit + 1;
}

void Scene::draw_on_board_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation, int posh, int posv)
{
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int tposh = m_shape_set->posh(shape_id, i, orientation);
        int tposv = m_shape_set->posv(shape_id, i, orientation);
        int x = on_board_tile_pos_x(rect, posh, tposh);
        int y = on_board_tile_pos_y(rect, posv, tposv);
        draw_tile(painter, x, y, shape_id, orientation, tposh, tposv);
    }
}

int Scene::off_board_tile_pos_x(const QRect& rect, int shape_id, int orientation, int tposh) const
{
    int cx = m_shape_set->horz_center(shape_id, orientation, m_unit);
    return rect.center().x() + tposh * m_unit - cx - m_unit / 2;
}

int Scene::off_board_tile_pos_y(const QRect& rect, int shape_id, int orientation, int tposv) const
{
    int cy = m_shape_set->vert_center(shape_id, orientation, m_unit);
    return rect.center().y() - tposv * m_unit + cy - m_unit / 2;
}

void Scene::draw_off_board_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation)
{
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int tposh = m_shape_set->posh(shape_id, i, orientation);
        int tposv = m_shape_set->posv(shape_id, i, orientation);
        int x = off_board_tile_pos_x(rect, shape_id, orientation, tposh);
        int y = off_board_tile_pos_y(rect, shape_id, orientation, tposv);
        draw_tile(painter, x, y, shape_id, orientation, tposh, tposv);
    }
}

bool Scene::mouse_test_off_board_shape(int mx, int my, const QRect& rect, int shape_id, int orientation) const
{
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int tposh = m_shape_set->posh(shape_id, i, orientation);
        int tposv = m_shape_set->posv(shape_id, i, orientation);
        int x = off_board_tile_pos_x(rect, shape_id, orientation, tposh);
        int y = off_board_tile_pos_y(rect, shape_id, orientation, tposv);
        if (mouse_test_tile(mx, my, x, y)) {
            return true;
        }
    }
    return false;
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

void Scene::mouse_left_press(int mx, int my)
{
    m_mouse_x = mx;
    m_mouse_y = my;
    m_first_mx = mx;
    m_first_my = my;
    m_left_down = false;
    bool left_down = mouse_test_pieces(mx, my, m_mouse_dock);
    if (left_down) {
        int pix = m_dock_list[m_mouse_dock];
        int shape_id = m_puzzle_book->shape_id(pix);
        int orientation = m_puzzle_book->orientation(pix);
        if (m_puzzle_book->on_board(pix)) {
//            if (!m_puzzle_book->locked(pix)) {
                int posh = m_puzzle_book->posh(pix);
                int posv = m_puzzle_book->posv(pix);
                m_offset_x = on_board_tile_pos_x(rack_rect(), posh, 0) - mx;
                m_offset_y = on_board_tile_pos_y(rack_rect(), posv, 0) - my + m_unit - 1;
                m_puzzle_book->lift_piece(pix);
                m_left_down = true;
//            }
        } else {
            m_offset_x = off_board_tile_pos_x(dock_rect(m_mouse_dock), shape_id, orientation, 0) - mx;
            m_offset_y = off_board_tile_pos_y(dock_rect(m_mouse_dock), shape_id, orientation, 0) - my + m_unit - 1;
            m_left_down = true;
        }
    }
}

void Scene::mouse_left_release(int mx, int my)
{
    if (m_left_down) {
        int pix = m_dock_list[m_mouse_dock];
        if (!m_puzzle_book->on_board(pix)) {
            int cx = m_mouse_x + m_offset_x + m_unit / 2;
            int cy = m_mouse_y + m_offset_y + m_unit / 2 - m_unit + 1;
            if (rack_rect().contains(cx, cy)) {
                int tposx = (cx - rack_rect().left()) / m_unit;
                int tposy = (rack_rect().bottom() - cy) / m_unit;
                int orientation = m_puzzle_book->orientation(pix);
                m_puzzle_book->drop_piece(m_shape_set, pix, orientation, tposx, tposy);
            }
        }
    }
    m_left_down = false;
    m_mouse_x = mx;
    m_mouse_y = my;
}

void Scene::mouse_right_press(int mx, int my)
{
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (dock_rect(i).contains(mx, my)) {
            int pix = m_dock_list[i];
            int orientation = m_puzzle_book->orientation(pix);
            orientation = (orientation ^ 4);
            if (((orientation & 3) == 0) || ((orientation & 3) == 3))
                orientation &= 5;
            else
                orientation |= 2;
            m_puzzle_book->set_orientation(pix, orientation);
        }
    }
}

void Scene::mouse_move(int mx, int my)
{
    if (m_left_down) {
        m_mouse_x = mx;
        m_mouse_y = my;
        int pix = m_dock_list[m_mouse_dock];
        if (m_puzzle_book->locked(pix)) {
            int thresh = 2 * m_unit;
            m_left_down = (abs(mx - m_first_mx) <= thresh) && (abs(my - m_first_my) <= thresh);
        }
    }
}

void Scene::mouse_wheel(int mx, int my, bool clockwise)
{
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (dock_rect(i).contains(mx, my)) {
            int pix = m_dock_list[i];
            if (!m_puzzle_book->on_board(pix)) {
                int orientation = m_puzzle_book->orientation(pix);
                orientation = (orientation & 4) | ((orientation + (clockwise ? -1 : 1)) & 3);
                m_puzzle_book->set_orientation(pix, orientation);
            }
        }
    }
}

bool Scene::mouse_test_pieces(int mx, int my, int& dock) const
{
    const PuzzleBook* pb = m_puzzle_book;
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        int pix = m_dock_list[i];
        if (m_puzzle_book->on_board(pix)) {
            if (mouse_test_on_board_shape(mx, my, rack_rect(), pb->shape_id(pix), pb->orientation(pix), pb->posh(pix), pb->posv(pix))) {
                dock = i;
                return true;
            }
        } else {
            if (mouse_test_off_board_shape(mx, my, dock_rect(i), pb->shape_id(pix), pb->orientation(pix))) {
                dock = i;
                return true;
            }
        }
    }
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
            return true;
        }
    }
    return false;
}

bool Scene::mouse_test_tile(int mx, int my, int sx, int sy) const
{
    return QRect(sx, sy, m_unit, m_unit).contains(mx, my);
}

void Scene::pb_next_challenge()
{
    m_puzzle_book->go_to_next_challenge();
}

void Scene::pb_previous_challenge()
{
    m_puzzle_book->go_to_previous_challenge();
}

void Scene::clear_board()
{
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (m_puzzle_book->on_board(i) && !m_puzzle_book->locked(i)) {
            m_puzzle_book->lift_piece(i);
        }
        if (!m_puzzle_book->on_board(i)) {
            m_puzzle_book->set_orientation(i, 0);
        }
    }
}

//
// scene.h
//
#if !defined(_SCENE_H_)
#define _SCENE_H_

#include <QPainter>
#include "shape_set.h"
#include "puzzle_book.h"

#define HORZ_UNITS 24
#define VERT_UNITS 18
#define BORDER_F 4

class Scene
{
public:
    Scene(PuzzleBook* puzzle_book, const ShapeSet* shape_set);
    ~Scene();
    void draw(QPainter& painter);
    void mouse_left_press(int mx, int my);
    void mouse_left_release(int mx, int my);
    void mouse_move(int mx, int my);
    void mouse_wheel(int mx, int my, bool clockwise);

protected:
    PuzzleBook* m_puzzle_book;
    const ShapeSet* m_shape_set;
    bool m_left_down;
    int  m_mouse_x;
    int  m_mouse_y;
    int m_mouse_dock;
    int m_xbase;
    int m_ybase;
    int m_scx;
    int m_scy;
    int m_unit;
    int m_docks;
    int m_dock_list[MAX_CHALLENGE_PIECES];

    void determine_layout(QPainter& painter);
    QRect rack_rect() const;
    QRect dock_rect(int dock_ix) const;

    void draw_rack(QPainter& painter);
    void draw_pieces(QPainter& painter);
    void draw_cursor(QPainter& painter);
    void draw_tile(QPainter& painter, int sx, int sy, int shape_id, int orientation, int tposh, int tposv);
    void draw_shape(QPainter& painter, int shape_id, int orientation, int sx, int sy);
    void draw_on_board_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation, int posh, int posv);
    void draw_off_board_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation);
    void map_docks();

    bool mouse_test_pieces(int mx, int my, int& dock) const;
    bool mouse_test_on_board_shape(int mx, int my, const QRect& rect, int shape_id, int orientation, int posh, int posv) const;
    bool mouse_test_off_board_shape(int mx, int my, const QRect& rect, int shape_id, int orientation) const;
    bool mouse_test_tile(int mx, int my, int sx, int sy) const;
};

#endif // _SCENE_H_

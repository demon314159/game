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

class Scene
{
public:
    Scene(const PuzzleBook* puzzle_book, const ShapeSet* shape_set);
    ~Scene();
    void draw(QPainter& painter);

protected:
    const PuzzleBook* m_puzzle_book;
    const ShapeSet* m_shape_set;
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
    void draw_tile(QPainter& painter, int sx, int sy, int shape_id, int orientation, int tposh, int tposv);
    void draw_on_board_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation, int posh, int posv);
    void draw_off_board_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation);
    void map_docks();
};

#endif // _SCENE_H_

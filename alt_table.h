//
// alt_table.h
//
#if !defined(_ALT_TABLE_H_)
#define _ALT_TABLE_H_

#include "table.h"
#include "image_set.h"
#include "ball.h"
#include "guy.h"
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QBasicTimer>

class AltTable: public QWidget
{
    Q_OBJECT

public:
    explicit AltTable(const QMatrix4x4& mvp_matrix, ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent = nullptr);

protected:
    const float BACK_WIDTH = 6.235;
//    const float FRONT_WIDTH = 5.529;
    const float FRONT_WIDTH = BACK_WIDTH;
    const float BACK_POS = -7.4;
    const float FRONT_POS = 2.0;
    const int TIMER_PERIOD = 33; // milliseconds

    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent*) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void draw_ani_image(QPainter &painter, const QRect& rect, const AnimatedImage& img, bool on_flag);
    void draw_ball(QPainter &painter, const QRect& rect);
    void draw_guy(QPainter &painter, const QRect& rect);
    void increment_score();
    int ball_radius(const QVector3D& position) const;
    int guy_radius(const QVector3D& position) const;
    QRect ball_rect(const QVector3D& position) const;
    QRect guy_rect(const QVector3D& position) const;
    QRect ball_last_rect() const;
    int target_hit(float x) const;
    QPoint w2s(const QVector3D point) const;
    void timerEvent(QTimerEvent *e) override;
    void my_update(const QRect& rect);

private:
    Ball m_ball;
    Guy m_guy;
    bool m_bat_on;
    bool m_pitch_on;
    bool m_target_on;
    int m_target_sel;
    int m_outs;
    int m_left_score;
    int m_middle_score;
    int m_right_score;
    int m_count_down;
    QImage m_ball_set;
    QImage m_guy_set;
    ImageSet& m_image_set;
    QStackedWidget* m_stacked_widget;
    int m_width;
    int m_height;
    const QMatrix4x4& m_mvp_matrix;
    QBasicTimer timer;
};

#endif // _ALT_TABLE_H_

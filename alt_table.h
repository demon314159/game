//
// alt_table.h
//
#if !defined(_ALT_TABLE_H_)
#define _ALT_TABLE_H_

#include "table.h"
#include "image_set.h"
#include "sprite.h"
#include "ball.h"
#include "guy.h"
#include "light_box.h"
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
    explicit AltTable(const QMatrix4x4& mvp_matrix, const QMatrix4x4& rot_matrix, ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent = nullptr);
    void new_game();

public slots:
    void new_game_ready();

signals:
    void game_over(int score);

protected:
    static const int MAX_GUYS = 4;
    const float WIDTH = 6.235;
    const float BACK_POS = -7.4;
    const float FRONT_POS = 2.0;
    const int TIMER_PERIOD = 33; // milliseconds

    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void draw_ani_image(QPainter& painter, const QRect& rect, const AnimatedImage& img, bool on_flag);
    void draw_lights(QPainter& painter, const QRect& rect);
    void increment_score();
    void check_score();
    bool any_guy_is_running() const;
    QVector3D corrected_sprite_position(const QVector3D& position, const Sprite& sprite);

    void bat_button_on();
    void bat_button_off();
    void pitch_button_on();
    void pitch_button_off();

    void update_guys();
    void launch_guys(int hit);
    void draw_guys(QPainter &painter, const QRect& rect);

    void update_sprite(Sprite& sprite);
    void draw_sprite(QPainter &painter, const QRect& rect, const Sprite& sprite);
    QRect sprite_rect(const QVector3D& position, const Sprite& sprite) const;
    int sprite_radius(const QVector3D& position, const Sprite& sprite) const;
    int target_hit(float x) const;
    QPoint w2s(const QVector3D point) const;
    void timerEvent(QTimerEvent *e) override;

private:
    LightBox m_light_box;
    Ball m_ball;
    Guy m_guy[MAX_GUYS];
    int m_guy_ix;
    bool m_bat_on;
    bool m_pitch_on;
    bool m_target_on;
    int m_target_sel;
    int m_outs;
    int m_left_score;
    int m_middle_score;
    int m_right_score;
    int m_count_down;
    ImageSet& m_image_set;
    QStackedWidget* m_stacked_widget;
    int m_width;
    int m_height;
    const QMatrix4x4& m_mvp_matrix;
    const QMatrix4x4& m_rot_matrix;
    QBasicTimer timer;
};

#endif // _ALT_TABLE_H_

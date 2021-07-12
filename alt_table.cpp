//
// alt_table.cpp
//
#include "alt_table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>

AltTable::AltTable(const QMatrix4x4& mvp_matrix, ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent)
    : QWidget(parent)
    , m_ball(BACK_WIDTH, FRONT_WIDTH, BACK_POS - BALL_RADIUS, FRONT_POS + BALL_RADIUS)
    , m_guy(-2.728265, 2.72865, -5.7412 + 0.1, 1.0 - 0.1)
    , m_bat_on(false)
    , m_pitch_on(false)
    , m_target_on(false)
    , m_target_sel(0)
    , m_outs(0)
    , m_left_score(0)
    , m_middle_score(0)
    , m_right_score(0)
    , m_count_down(0)
    , m_image_set(image_set)
    , m_stacked_widget(stacked_widget)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_mvp_matrix(mvp_matrix)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMinimumHeight(980);
    setMinimumWidth(580);
    timer.start(TIMER_PERIOD, this);
}

void AltTable::draw_ani_image(QPainter &painter, const QRect& rect, const AnimatedImage& img, bool on_flag)
{
    if (rect.intersects(img.rect())) {
        if (on_flag) {
            painter.drawImage(img.m_x, img.m_y, img.m_image);
        }
    }
}

void AltTable::draw_sprite(QPainter &painter, const QRect& rect, const Sprite& sprite)
{
    QVector3D sprite_pos = sprite.position();
    if (rect.intersects(sprite_rect(sprite_pos, sprite))) {
        int sr = sprite_radius(sprite_pos, sprite);
        if (sr >= 1 && sr <= 64) {
            int xp = ((sr - 1) & 7) * 128;
            int yp = (((sr - 1) >> 3) & 7) * 128;
            int bx = std::max(xp, xp + 64 - sr - 2);
            int by = std::max(yp, yp + 64 - sr - 2);
            int sx = std::min(2 * sr + 4, 128);
            QPoint screen_pos = w2s(sprite_pos);
            painter.drawImage(screen_pos.x() - sx / 2, screen_pos.y() - sx / 2, sprite.copy(bx, by, sx, sx));
        } else {
            printf("<<< sprite radius our of range: %d pixels >>>\n", sr);
        }
    }
}

QRect AltTable::sprite_rect(const QVector3D& position, const Sprite& sprite) const
{
    QPoint screen_pos = w2s(position);
    int screen_radius = sprite_radius(position, sprite);

    return QRect(std::max(0, screen_pos.x() - screen_radius - 2),
                 std::max(0, screen_pos.y() - screen_radius - 2),
                 2 * screen_radius + 4,
                 2 * screen_radius + 4);
}

int AltTable::sprite_radius(const QVector3D& position, const Sprite& sprite) const
{
    QVector3D pos_left = position + QVector3D(-sprite.radius(), 0.0, 0.0);
    QVector3D pos_right = position + QVector3D(sprite.radius(), 0.0, 0.0);
    QPoint bl = w2s(pos_left);
    QPoint br = w2s(pos_right);
    return (br.x() - bl.x() + 1) / 2;
}

void AltTable::paintEvent(QPaintEvent* event)
{
    QRect rect = event->rect();
    QPainter painter(this);
    // w2s() function depends on these
    m_width = painter.viewport().width();
    m_height = painter.viewport().height();

//    printf("rect = (%d, %d) %d * %d\n", rect.x(), rect.y(), rect.width(), rect.height());

    if (rect == painter.viewport()) {
        painter.drawImage(0, 0, m_image_set.m_baseline);
    } else {
        QImage base_rect = m_image_set.m_baseline.copy(rect);
        painter.drawImage(rect.x(), rect.y(), base_rect);
    }
    draw_ani_image(painter, rect, m_image_set.m_pitch, m_pitch_on);

    draw_ani_image(painter, rect, m_image_set.m_target[m_target_sel], m_target_on);
    if (m_outs > 0) {
        draw_ani_image(painter, rect, m_image_set.m_outs[m_outs - 1], true);
    }
    draw_ani_image(painter, rect, m_image_set.m_left_digit[m_left_score], true);
    draw_ani_image(painter, rect, m_image_set.m_middle_digit[m_middle_score], true);
    draw_ani_image(painter, rect, m_image_set.m_right_digit[m_right_score], true);
    draw_ani_image(painter, rect, m_image_set.m_bat, m_bat_on);

    draw_sprite(painter, rect, m_ball);
    if (m_guy.in_play())
      draw_sprite(painter, rect, m_guy);
}

void AltTable::resizeEvent(QResizeEvent*)
{
    if (isVisible()) {
        printf("resize handback\n");
        m_stacked_widget->setCurrentIndex(0);
    }
}

void AltTable::mousePressEvent(QMouseEvent *e)
{
    if (m_count_down == 0) {
        if (e->button() == Qt::LeftButton) {
            m_bat_on = true;
            update(m_image_set.m_bat.rect());
            m_ball.hit(QVector3D(BAT_PIVOT_X, 0.0, BAT_PIVOT_Z));
        } else if (e->button() == Qt::RightButton) {
            if (!m_ball.in_play()) {
                m_ball.launch(QVector3D(0.0, BALL_RADIUS, -2.0));
                m_pitch_on = true;
                update(m_image_set.m_pitch.rect());
            }
        }
    }
}

void AltTable::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_bat_on = false;
        update(m_image_set.m_bat.rect());
    } else if (e->button() == Qt::RightButton) {
        m_pitch_on = false;
        update(m_image_set.m_pitch.rect());
    }
}

int AltTable::target_hit(float x) const
{
    for (int i = 0; i < 7 ; i++) {
        float xl = (-6.5 + 2.0 * (float) i) * TARGET_WIDTH;
        float xr = (-5.5 + 2.0 * (float) i) * TARGET_WIDTH;
        if (x >= xl && x <= xr) {
            return i + 1;
        }
    }
    return 0;
}

QPoint AltTable::w2s(const QVector3D point) const
{

    QVector4D sp = m_mvp_matrix * QVector4D(point, 1.0);
    QPoint res(m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w())),
               m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w())));
    return res;
}

void AltTable::increment_score()
{
    QRect old_score_rect1 = m_image_set.m_left_digit[m_left_score].rect();
    QRect old_score_rect2 = m_image_set.m_middle_digit[m_middle_score].rect();
    QRect old_score_rect3 = m_image_set.m_right_digit[m_right_score].rect();
    bool carry = m_right_score == 9;
    m_right_score = carry ? 0 : m_right_score + 1;
    if (carry) {
        carry = m_middle_score == 9;
        m_middle_score = carry ? 0 : m_middle_score + 1;
        if (carry) {
            carry = m_left_score == 9;
            m_left_score = carry ? 0 : m_left_score + 1;
        }
    }
    QRect new_score_rect1 = m_image_set.m_left_digit[m_left_score].rect();
    QRect new_score_rect2 = m_image_set.m_middle_digit[m_middle_score].rect();
    QRect new_score_rect3 = m_image_set.m_right_digit[m_right_score].rect();

    update(old_score_rect1);
    update(old_score_rect2);
    update(old_score_rect3);
    update(new_score_rect1);
    update(new_score_rect2);
    update(new_score_rect3);
}

void AltTable::timerEvent(QTimerEvent *)
{
    m_guy.update();
    QRect gr_before = sprite_rect(m_guy.last_position(), m_guy);
    QRect gr_after = sprite_rect(m_guy.position(), m_guy);
    update(gr_before);
    update(gr_after);
    if (m_count_down > 0) {
        if (m_count_down == (400 / TIMER_PERIOD) - 2) {
           increment_score();
           m_guy.launch(0.0, 2.0);
        }
        if (m_count_down == 1) {
            m_target_on = false;
            m_ball.reset();
            update();
        }
        --m_count_down;
    } else {
        if (m_ball.in_play()) {
            m_ball.update();
            QRect br_before = sprite_rect(m_ball.last_position(), m_ball);
            QRect br_after = sprite_rect(m_ball.position(), m_ball);
            update(br_before);
            update(br_after);
        } else if (m_ball.stopped()) {
            if (m_ball.position().z() < BACK_POS) {
                int t1 = target_hit(m_ball.position().x() - BALL_RADIUS * 1.1);
                int t2 = target_hit(m_ball.position().x() + BALL_RADIUS * 1.1);
                if (t1 > 0 || t2 > 0) {
                    m_target_sel = (t1 | t2) - 1;
                    m_target_on = true;
                    update(m_image_set.m_target[m_target_sel].rect());
                } else {
                    if (m_outs < 3) {
                        ++m_outs;
                        update(m_image_set.m_outs[m_outs - 1].rect());
                    }
                }

            }
            m_count_down = 400 / TIMER_PERIOD;
        }
    }
}


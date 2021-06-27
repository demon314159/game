//
// alt_table.cpp
//
#include "alt_table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>

AltTable::AltTable(const QMatrix4x4& mvp_matrix, ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent)
    : QWidget(parent)
    , m_bat_on(false)
    , m_pitch_on(false)
    , m_image_set(image_set)
    , m_stacked_widget(stacked_widget)
    , m_x_base(0)
    , m_y_base(0)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_mvp_matrix(mvp_matrix)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMinimumHeight(980);
    setMinimumWidth(580);
}

int AltTable::text_width(QPainter& painter, const QString &s)
{
    QRect rect = painter.boundingRect(0, 0, 0, 0, 0, s);
    return rect.width();
}

int AltTable::text_height(QPainter& painter, const QString &s)
{
    QRect rect = painter.boundingRect(0, 0, 0, 0, 0, s);
    return rect.height();
}


void AltTable::draw_ani_image(QPainter &painter, const QRect& rect, const AnimatedImage& img, bool on_flag)
{
    if (rect == img.rect()) {
        if (on_flag) {
            painter.drawImage(img.m_x, img.m_y, img.m_on_image);
            printf("drawing little picture on\n");
        } else {
            painter.drawImage(img.m_x, img.m_y, img.m_off_image);
            printf("drawing little picture off\n");
        }
    }
}

void AltTable::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
//    int th = text_height(painter, QString("0"));

//    painter.setPen(Qt::black);
   QRect rect = event->rect();
   printf("rect = (%d, %d) %d * %d\n", rect.x(), rect.y(), rect.width(), rect.height());

    m_width = painter.viewport().width();
    m_height = painter.viewport().height();
    m_x_base = painter.viewport().left();
    m_y_base = painter.viewport().top();


    if (rect == painter.viewport()) {
        painter.drawImage(0, 0, m_image_set.m_baseline);
        printf("drawing big picture\n");
    }
    draw_ani_image(painter, rect, m_image_set.m_bat, m_bat_on);
    draw_ani_image(painter, rect, m_image_set.m_pitch, m_pitch_on);
#ifdef NEVERMORE

        draw_ani_image(painter, m_image_set.m_target1);
    else if (m_image_sel == 4)
        draw_ani_image(painter, m_image_set.m_target2);
    else if (m_image_sel == 5)
        draw_ani_image(painter, m_image_set.m_target3);
    else if (m_image_sel == 6)
        draw_ani_image(painter, m_image_set.m_target4);
    else if (m_image_sel == 7)
        draw_ani_image(painter, m_image_set.m_target5);
    else if (m_image_sel == 8)
        draw_ani_image(painter, m_image_set.m_target6);
    else if (m_image_sel == 9)
        draw_ani_image(painter, m_image_set.m_target7);
#endif
    printf("paint (%d, %d) %d * %d\n", m_x_base, m_y_base, m_width, m_height);
    painter.setPen(Qt::black);

    QVector4D tp1(-5.529 / 2.0, 0.0, 2.0, 1.0);
    QVector4D tp2(5.529 / 2.0, 0.0, 2.0, 1.0);
    QVector4D tp3(6.235 / 2.0, 0.0, -7.4, 1.0);
    QVector4D tp4(-6.235 / 2.0, 0.0, -7.4, 1.0);
    QVector4D rp1 = m_mvp_matrix * tp1;
    QVector4D rp2 = m_mvp_matrix * tp2;
    QVector4D rp3 = m_mvp_matrix * tp3;
    QVector4D rp4 = m_mvp_matrix * tp4;


    rp1 =  (1.0 / rp1.w()) * rp1;
    rp2 =  (1.0 / rp2.w()) * rp2;
    rp3 =  (1.0 / rp3.w()) * rp3;
    rp4 =  (1.0 / rp4.w()) * rp4;

    printf("rp1 = %7.3f, %7.3f\n",
           rp1.x() / rp1.w(), rp1.y() / rp1.w());
    printf("rp2 = %7.3f, %7.3f\n",
           rp2.x() / rp2.w(), rp2.y() / rp2.w());
    printf("rp3 = %7.3f, %7.3f\n",
           rp3.x() / rp3.w(), rp3.y() / rp3.w());
    printf("rp4 = %7.3f, %7.3f\n",
           rp4.x() / rp4.w(), rp4.y() / rp4.w());

    float x1 = (m_width / 2) * rp1.x();
    float y1 = -(m_height / 2) * rp1.y();

    float x2 = (m_width / 2) * rp2.x();
    float y2 = -(m_height / 2) * rp2.y();

    float x3 = (m_width / 2) * rp3.x();
    float y3 = -(m_height / 2) * rp3.y();

    float x4 = (m_width / 2) * rp4.x();
    float y4 = -(m_height / 2) * rp4.y();

    printf("x1,y1 = %7.3f, %7.3f\n", x1, y1);
    printf("x2,y2 = %7.3f, %7.3f\n", x2, y2);
    printf("x3,y3 = %7.3f, %7.3f\n", x3, y3);
    printf("x4,y4 = %7.3f, %7.3f\n", x4, y4);

    painter.drawLine(m_width / 2 + x1, m_height / 2 + y1, m_width / 2 + x2, m_height / 2 + y2);
    painter.drawLine(m_width / 2 + x2, m_height / 2 + y2, m_width / 2 + x3, m_height / 2 + y3);
    painter.drawLine(m_width / 2 + x3, m_height / 2 + y3, m_width / 2 + x4, m_height / 2 + y4);
    painter.drawLine(m_width / 2 + x4, m_height / 2 + y4, m_width / 2 + x1, m_height / 2 + y1);

//    painter.drawRect(QRect(m_width / 2 + x1, m_height / 2 + y1, x2 - x1, y2 - y1));
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
    if (e->button() == Qt::LeftButton) {
        m_bat_on = true;
        update(m_image_set.m_bat.rect());
    } else if (e->button() == Qt::RightButton) {
        m_pitch_on = true;
        update(m_image_set.m_pitch.rect());
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

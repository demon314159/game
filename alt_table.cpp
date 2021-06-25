//
// alt_table.cpp
//
#include "alt_table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>

AltTable::AltTable(ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent)
    : QWidget(parent)
    , m_bat_on(false)
    , m_pitch_on(false)
    , m_image_set(image_set)
    , m_stacked_widget(stacked_widget)
    , m_x_base(0)
    , m_y_base(0)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
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

//    painter.setPen(Qt::black);
//    painter.drawRect(QRect(m_x_base,
//                           m_y_base,
//                           m_width - 1,
//                           m_height));
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

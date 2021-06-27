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


    QVector3D tp1(-5.529 / 2.0, 0.0, 2.0);
    QVector3D tp2(5.529 / 2.0, 0.0, 2.0);
    QVector3D tp3(6.235 / 2.0, 0.0, -7.4);
    QVector3D tp4(-6.235 / 2.0, 0.0, -7.4);

    QPoint sp1 = w2s(tp1);
    QPoint sp2 = w2s(tp2);
    QPoint sp3 = w2s(tp3);
    QPoint sp4 = w2s(tp4);

    float x1 = sp1.x();
    float y1 = sp1.y();

    float x2 = sp2.x();
    float y2 = sp2.y();

    float x3 = sp3.x();
    float y3 = sp3.y();

    float x4 = sp4.x();
    float y4 = sp4.y();

    printf("x1,y1 = %7.3f, %7.3f\n", x1, y1);
    printf("x2,y2 = %7.3f, %7.3f\n", x2, y2);
    printf("x3,y3 = %7.3f, %7.3f\n", x3, y3);
    printf("x4,y4 = %7.3f, %7.3f\n", x4, y4);

    painter.drawLine(x1, y1, x2, y2);
    painter.drawLine(x2, y2, x3, y3);
    painter.drawLine(x3, y3, x4, y4);
    painter.drawLine(x4, y4, x1, y1);
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

QPoint AltTable::w2s(const QVector3D point) const
{

    QVector4D sp = m_mvp_matrix * QVector4D(point, 1.0);
    QPoint res(m_x_base + m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w())),
               m_y_base + m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w())));
    return res;
}


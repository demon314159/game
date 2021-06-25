//
// alt_table.h
//
#if !defined(_ALT_TABLE_H_)
#define _ALT_TABLE_H_

#include "table.h"
#include "image_set.h"
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QStackedWidget>

class AltTable: public QWidget
{
    Q_OBJECT

public:
    explicit AltTable(ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent = nullptr);

protected:
    int text_width(QPainter& painter, const QString &s);
    int text_height(QPainter& painter, const QString &s);
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent*) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void draw_ani_image(QPainter &painter, const QRect& rect, const AnimatedImage& img, bool on_flag);

private:
    bool m_bat_on;
    bool m_pitch_on;
    ImageSet& m_image_set;
    QStackedWidget* m_stacked_widget;
    int m_x_base;
    int m_y_base;
    int m_width;
    int m_height;
    QPixmap m_pixmap;
};

#endif // _ALT_TABLE_H_

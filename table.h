//
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

class Table: public QWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);

protected:
    int text_width(QPainter& painter, const QString &s);
    int text_height(QPainter& painter, const QString &s);
    void paintEvent(QPaintEvent* event) override;

private:
    int m_x_base;
    int m_y_base;
    int m_width;
    int m_height;
    QPixmap m_pixmap;
};

#endif // _TABLE_H_

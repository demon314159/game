//
// alt_table.h
//
#if !defined(_ALT_TABLE_H_)
#define _ALT_TABLE_H_

#include "table.h"
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

class AltTable: public QWidget
{
    Q_OBJECT

public:
    explicit AltTable(Table* the_table, QWidget *parent = nullptr);

protected:
    int text_width(QPainter& painter, const QString &s);
    int text_height(QPainter& painter, const QString &s);
    void paintEvent(QPaintEvent* event) override;

private:
    Table* m_the_table;
    int m_x_base;
    int m_y_base;
    int m_width;
    int m_height;
    QPixmap m_pixmap;
};

#endif // _ALT_TABLE_H_

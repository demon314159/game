//
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include <QObject>
#include <QWidget>
#include <QPainter>

#include "scene.h"
#include "shape_set.h"

class Table: public QWidget
{
    Q_OBJECT

public:
    explicit Table(const ShapeSet* shape_set, QWidget *parent = nullptr);
    void next_shape();
    void prev_shape();

protected:
    int text_width(QPainter& painter, const QString &s);
    int text_height(QPainter& painter, const QString &s);
    void paintEvent(QPaintEvent* event) override;

private:
    Scene m_scene;
};

#endif // _TABLE_H_

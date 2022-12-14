//
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include <QObject>
#include <QWidget>
#include <QPainter>

#include "scene.h"

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
    Scene m_scene;
};

#endif // _TABLE_H_

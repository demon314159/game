//
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPushButton>

class Table: public QWidget
{
    Q_OBJECT

public:
    explicit Table(QPushButton* previous_button, QPushButton* next_button, QPushButton* clear_button, QWidget *parent);
    void show_help();

protected:
    int text_width(QPainter& painter, const QString &s);
    int text_height(QPainter& painter, const QString &s);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void full_update();


private:
    QWidget* m_parent;
    QPushButton* m_previous_button;
    QPushButton* m_next_button;
    QPushButton* m_clear_button;
};

#endif // _TABLE_H_

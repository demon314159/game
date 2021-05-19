//
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Table: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // _TABLE_H_

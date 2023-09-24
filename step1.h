//
// step1.h
//
#ifndef _STEP1_H_
#define _STEP1_H_

#include <QMainWindow>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>
#include "table.h"

class Step1: public QMainWindow
{
    Q_OBJECT

public:
    Step1();
    ~Step1();

private:
    void initializeWindow();
    void pb_update();

private slots:
    void pb1();
    void pb2();
    void pb3();
    void pb4();
    void pb5();

private:
    // Owned by layout
    Table *m_table = nullptr;
    QPushButton *m_pb1 = nullptr;
    QPushButton *m_pb2 = nullptr;
    QPushButton *m_pb3 = nullptr;
    QPushButton *m_pb4 = nullptr;
    QPushButton *m_pb5 = nullptr;
};

#endif // _STEP1_H

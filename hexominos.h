//
// hexominos.h
//
#ifndef _HEXOMINOS_H_
#define _HEXOMINOS_H_

#include <QMainWindow>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>
#include "table.h"
#include "puzzle.h"
#include "full_set.h"

class Hexominos: public QMainWindow
{
    Q_OBJECT

public:
    Hexominos(const Puzzle& puzzle, const FullSet& fullset);
    ~Hexominos();

private:
    void initializeWindow();

private slots:
    void pb1();
    void pb2();
    void pb3();
    void pb4();
    void pb5();

private:
    const Puzzle& m_puzzle;
    const FullSet& m_full_set;
    // Owned by layout
    Table *m_table = nullptr;
    QPushButton *m_pb1 = nullptr;
    QPushButton *m_pb2 = nullptr;
    QPushButton *m_pb3 = nullptr;
    QPushButton *m_pb4 = nullptr;
    QPushButton *m_pb5 = nullptr;
};

#endif // _HEXOMINOS_H

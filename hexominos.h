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
#include "puzzle_book.h"
#include "shape_set.h"
#include "history.h"

class Hexominos: public QMainWindow
{
    Q_OBJECT

public:
    Hexominos(PuzzleBook* puzzle_book, ShapeSet* shape_set);
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
    PuzzleBook* m_puzzle_book;
    ShapeSet* m_shape_set;
    History m_history;
    // Owned by layout
    Table *m_table = nullptr;
    QPushButton *m_pb1 = nullptr;
    QPushButton *m_pb2 = nullptr;
    QPushButton *m_pb3 = nullptr;
    QPushButton *m_pb4 = nullptr;
    QPushButton *m_pb5 = nullptr;
};

#endif // _HEXOMINOS_H

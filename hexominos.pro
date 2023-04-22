TEMPLATE = app
TARGET = hexominos

QT += widgets

## CONFIG += qt debug

HEADERS       = hexominos.h \
                pos_rec.h \
                table.h \
                challenge.h \
                shape.h \
                piece.h \
                puzzle_book.h \
                shape_set.h \
                scene.h

SOURCES       = main.cpp \
                hexominos.cpp \
                table.cpp \
                challenge.cpp \
                shape.cpp \
                piece.cpp \
                puzzle_book.cpp \
                shape_set.cpp \
                scene.cpp


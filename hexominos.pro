TEMPLATE = app
TARGET = hexominos

QT += multimedia widgets

## CONFIG += qt debug

HEADERS       = hexominos.h \
                moverec.h \
                posrec.h \
                table.h \
                challenge.h \
                piece.h \
                puzzle_book.h \
                full_set.h

SOURCES       = main.cpp \
                hexominos.cpp \
                table.cpp \
                challenge.cpp \
                piece.cpp \
                puzzle_book.cpp \
                full_set.cpp


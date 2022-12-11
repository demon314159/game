TEMPLATE = app
TARGET = hexominos

QT += multimedia widgets

## CONFIG += qt debug

HEADERS       = hexominos.h \
                move_rec.h \
                pos_rec.h \
                table.h \
                challenge.h \
                shape.h \
                puzzle_book.h \
                full_set.h \
                command.h \
                history.h

SOURCES       = main.cpp \
                hexominos.cpp \
                table.cpp \
                challenge.cpp \
                shape.cpp \
                puzzle_book.cpp \
                full_set.cpp \
                command.cpp \
                history.cpp


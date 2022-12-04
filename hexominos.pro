TEMPLATE = app
TARGET = hexominos

QT += multimedia widgets

## CONFIG += qt debug

HEADERS       = hexominos.h \
                moverec.h \
                table.h \
                challenge.h

SOURCES       = main.cpp \
                hexominos.cpp \
                table.cpp \
                challenge.cpp


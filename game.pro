TEMPLATE = app
TARGET = game

QT += multimedia widgets

## CONFIG += qt debug

HEADERS       = game.h \
                table.h \
                puck.h

SOURCES       = main.cpp \
                game.cpp \
                table.cpp \
                puck.cpp


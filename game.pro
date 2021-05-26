TEMPLATE = app
TARGET = game

QT += multimedia widgets

## CONFIG += qt debug

HEADERS      += game.h \
                table.h \
                puck.h \
                cad_model.h \
                matrix.h \
                thingus.h

SOURCES      += main.cpp \
                game.cpp \
                table.cpp \
                puck.cpp \
                cad_model.cpp \
                matrix.cpp \
                thingus.cpp

RESOURCES    += shaders.qrc \
                textures.qrc


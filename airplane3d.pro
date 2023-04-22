TEMPLATE = app
TARGET = airplane3d

QT += widgets
QT += opengl
QT += openglwidgets

## CONFIG += qt debug

HEADERS      += game.h \
                int3.h \
                float3.h \
                qa.h \
                table.h \
                paint_can.h \
                bin_interface.h \
                char_interface.h \
                token_interface.h \
                vrml_interface.h \
                stl_interface.h \
                cad_model.h \
                thingus.h

SOURCES      += main.cpp \
                game.cpp \
                qa.cpp \
                table.cpp \
                paint_can.cpp \
                bin_interface.cpp \
                char_interface.cpp \
                token_interface.cpp \
                vrml_interface.cpp \
                stl_interface.cpp \
                cad_model.cpp \
                thingus.cpp

RESOURCES    += shaders.qrc
RESOURCES    += models.qrc


TEMPLATE = app
TARGET = game

QT += multimedia widgets

## CONFIG += qt debug

HEADERS      += game.h \
                int3.h \
                float3.h \
                table.h \
                alt_table.h \
                puck.h \
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
                table.cpp \
                alt_table.cpp \
                puck.cpp \
                paint_can.cpp \
                bin_interface.cpp \
                char_interface.cpp \
                token_interface.cpp \
                vrml_interface.cpp \
                stl_interface.cpp \
                cad_model.cpp \
                thingus.cpp

RESOURCES    += shaders.qrc \
                textures.qrc


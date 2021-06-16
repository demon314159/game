TEMPLATE = app
TARGET = game

QT += multimedia widgets

## CONFIG += qt debug

HEADERS      += game.h \
                int3.h \
                float3.h \
                table.h \
                puck.h \
                bin_interface.h \
                char_interface.h \
                token_interface.h \
                vrml_interface.h \
                stl_interface.h \
                cad_model.h \
                vrml_model.h \
                stl_model.h \
                thingus.h

SOURCES      += main.cpp \
                game.cpp \
                table.cpp \
                puck.cpp \
                bin_interface.cpp \
                char_interface.cpp \
                token_interface.cpp \
                vrml_interface.cpp \
                stl_interface.cpp \
                cad_model.cpp \
                vrml_model.cpp \
                stl_model.cpp \
                thingus.cpp

RESOURCES    += shaders.qrc \
                textures.qrc


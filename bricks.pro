TEMPLATE = app
TARGET = bricks

QT += widgets

## CONFIG += qt debug

HEADERS      += game.h \
                int3.h \
                float3.h \
                facet.h \
                bounding_box.h \
                shape.h \
                table.h \
                paint_can.h \
                cube_shape.h \
                brick_shape.h \
                elements.h \
                document.h \
                bin_interface.h \
                char_interface.h \
                token_interface.h \
                vrml_interface.h \
                stl_interface.h \
                cad_model.h \
                frame_model.h \
                window_model.h \
                thingus.h

SOURCES      += main.cpp \
                game.cpp \
                table.cpp \
                paint_can.cpp \
                cube_shape.cpp \
                brick_shape.cpp \
                elements.cpp \
                document.cpp \
                bin_interface.cpp \
                char_interface.cpp \
                token_interface.cpp \
                vrml_interface.cpp \
                stl_interface.cpp \
                cad_model.cpp \
                frame_model.cpp \
                window_model.cpp \
                thingus.cpp

RESOURCES    += shaders.qrc


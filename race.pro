TEMPLATE = app
TARGET = race

QT += widgets

## CONFIG += qt debug

HEADERS      += game.h \
                int3.h \
                float3.h \
                facet.h \
                face.h \
                vertex_data.h \
                paint_can.h \
                bounding_box.h \
                look.h \
                track_style.h \
                shape.h \
                table.h \
                navigate.h \
                bin_interface.h \
                char_interface.h \
                token_interface.h \
                vrml_interface.h \
                stl_interface.h \
                cad_model.h \
                view.h \
                brick_shape.h \
                cube_shape.h \
                track_shape.h \

SOURCES      += main.cpp \
                game.cpp \
                paint_can.cpp \
                look.cpp \
                track_style.cpp \
                table.cpp \
                navigate.cpp \
                bin_interface.cpp \
                char_interface.cpp \
                token_interface.cpp \
                vrml_interface.cpp \
                stl_interface.cpp \
                cad_model.cpp \
                view.cpp \
                brick_shape.cpp \
                cube_shape.cpp \
                track_shape.cpp \

RESOURCES    += shaders.qrc


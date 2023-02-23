E
TEMPLATE = app
TARGET = race

QT += widgets

## CONFIG += qt debug

HEADERS      += game.h \
                int3.h \
                float3.h \
                double3.h \
                matrix.h \
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
                box_shape.h \
                ring_shape.h \
                cylinder_shape.h \
                straight_track_shape.h \
                curved_track_shape.h \
                section.h \
                straight_section.h \
                curved_section.h \
                track.h \
                car.h \
                qa.h \

SOURCES      += main.cpp \
                game.cpp \
                matrix.cpp \
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
                box_shape.cpp \
                ring_shape.cpp \
                cylinder_shape.cpp \
                straight_track_shape.cpp \
                curved_track_shape.cpp \
                section.cpp \
                straight_section.cpp \
                curved_section.cpp \
                track.cpp \
                car.cpp \
                qa.cpp \

RESOURCES    += shaders.qrc


TEMPLATE = app
TARGET = bricks

QT += widgets

## CONFIG += qt debug

HEADERS      += game.h \
                int3.h \
                float3.h \
                facet.h \
                face.h \
                choice.h \
                bounding_box.h \
                shape.h \
                table.h \
                paint_can.h \
                look.h \
                cube_shape.h \
                brick_shape.h \
                roof_shape.h \
                gable_brick_shape.h \
                arrow_shape.h \
                morph_shape.h \
                done_shape.h \
                background_shape.h \
                cancel_shape.h \
                element.h \
                morph_element.h \
                mouse_vector.h \
                mouse_vector_shape.h \
                command.h \
                history.h \
                choose.h \
                navigate.h \
                vmenu.h \
                document.h \
                bin_interface.h \
                char_interface.h \
                token_interface.h \
                vrml_interface.h \
                stl_interface.h \
                cad_model.h \
                frame_model.h \
                window_model.h \
                door_model.h \
                view.h

SOURCES      += main.cpp \
                game.cpp \
                table.cpp \
                paint_can.cpp \
                look.cpp \
                cube_shape.cpp \
                brick_shape.cpp \
                roof_shape.cpp \
                gable_brick_shape.cpp \
                arrow_shape.cpp \
                morph_shape.cpp \
                done_shape.cpp \
                background_shape.cpp \
                cancel_shape.cpp \
                element.cpp \
                morph_element.cpp \
                mouse_vector.cpp \
                mouse_vector_shape.cpp \
                command.cpp \
                history.cpp \
                choose.cpp \
                navigate.cpp \
                vmenu.cpp \
                document.cpp \
                bin_interface.cpp \
                char_interface.cpp \
                token_interface.cpp \
                vrml_interface.cpp \
                stl_interface.cpp \
                cad_model.cpp \
                frame_model.cpp \
                window_model.cpp \
                door_model.cpp \
                view.cpp

RESOURCES    += shaders.qrc


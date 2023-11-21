
HEADERS = view.h \
          pi.h \
          table.h \
          matrix4x4.h \
          matrix3x3.h \
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
          navigate.h \
          cad_model.h \
          view.h \
          brick_shape.h \
          cube_shape.h \
          box_shape.h \
          ring_shape.h \
          rise_profile.h \
          cylinder_shape.h \
          straight_track_shape.h \
          curved_right_track_shape.h \
          curved_left_track_shape.h \
          section.h \
          anchor.h \
          straight_section.h \
          curved_right_section.h \
          curved_left_section.h \
          track.h \
          car.h \
          qa.h \

OBJECTS = main.obj \
          view.obj \
          table.obj \
          matrix4x4.obj \
          matrix3x3.obj \
          matrix.obj \
          paint_can.obj \
          look.obj \
          track_style.obj \
          navigate.obj \
          cad_model.obj \
          brick_shape.obj \
          cube_shape.obj \
          box_shape.obj \
          ring_shape.obj \
          rise_profile.obj \
          cylinder_shape.obj \
          straight_track_shape.obj \
          curved_right_track_shape.obj \
          curved_left_track_shape.obj \
          section.obj \
          straight_section.obj \
          curved_right_section.obj \
          curved_left_section.obj \
          track.obj \
          car.obj \
          qa.obj \

LIBPATH = /libpath:c:/users/demon/sdl2/lib/x64 /libpath:c:/users/demon/glew/lib/Release/x64
INCPATH = /Ic:/users/demon/sdl2/include /Ic:/users/demon/glew/include
LIBRARIES = opengl32.lib glew32.lib SDL2main.lib SDL2.lib shell32.lib
DEPS = $(HEADERS)
CXX = cl
LXX = link
CXXFLAGS = /c
LINKFLAGS = /SUBSYSTEM:CONSOLE
TARGET = race.exe

%.obj: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(INCPATH) /Fo$@ $<

$(TARGET): $(OBJECTS)
	$(LXX) /out:$@ $(OBJECTS) $(LIBPATH) $(LIBRARIES) $(LINKFLAGS)

i.PHONY: clean

clean:
	rm *.o




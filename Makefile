
HEADERS = view.h \
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

OBJECTS = main.o \
          view.o \
          table.o \
          matrix4x4.o \
          matrix3x3.o \
          matrix.o \
          paint_can.o \
          look.o \
          track_style.o \
          navigate.o \
          cad_model.o \
          view.o \
          brick_shape.o \
          cube_shape.o \
          box_shape.o \
          ring_shape.o \
          cylinder_shape.o \
          straight_track_shape.o \
          curved_right_track_shape.o \
          curved_left_track_shape.o \
          section.o \
          straight_section.o \
          curved_right_section.o \
          curved_left_section.o \
          track.o \
          car.o \
          qa.o \

DEPS = $(HEADERS)
INCPATH = -I. `sdl2-config --cflags`
CXX = g++
CXXFLAGS = $(INCPATH)
LIBS = -lGLEW -lGLU -lGL `sdl2-config --libs`

%.o: %.cpp $(DEPS)
	$(CXX) -c -Wall -o $@ $< $(CXXFLAGS)

race: $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

i.PHONY: clean

clean:
	rm *.o




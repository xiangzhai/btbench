COMMONFLAGS= -g -Wall
OBJCFLAGS=`pkg-config --cflags cairo glib-2.0` -std=c99
CFLAGS=`pkg-config --cflags cairo glib-2.0` -g -Wall
CXXFLAGS=`pkg-config --cflags gtkmm-2.4 cairo glib-2.0` -g -Wall

LIBS_CAIRO=`pkg-config --libs cairo glib-2.0`
LIBS_COCOA=`pkg-config --libs cairo glib-2.0` -framework Cocoa
LIBS_GTKMM=`pkg-config --libs gtkmm-2.4 cairomm-1.0 glib-2.0`

all: cairo_cg cairo_gtk

run_cg: cairo_cg
	./CairoCG.app/Contents/MacOS/CairoCG

run_gtk: cairo_gtk
	./CairoGtk.app/Contents/MacOS/CairoGtk

run_img: cairo_img
	./cairo_img

cairo_cg: cairo_cg.m
	$(OBJC) $(OBJCFLAGS) $(COMMONFLAGS) $^ $(LIBS_COCOA) -o $@
	cp cairo_cg CairoCG.app/Contents/MacOS/CairoCG

cairo_gtk: cairo_gtk.cc
	$(CXX) $(CXXFLAGS) $(COMMONFLAGS) $^ $(LIBS_GTKMM) -o $@
	cp cairo_gtk CairoGtk.app/Contents/MacOS/CairoGtk

cairo_img: cairo_img.c
	$(CC) $(CFLAGS) $(COMMONFLAGS) $^ $(LIBS_CAIRO) -o $@

clean:
	rm -f cairo_cg cairo_gtk cairo_img
	rm -f CairoCG.app/Contents/MacOS/CairoGtk
	rm -f CairoCG.app/Contents/MacOS/CairoCG

.PHONY: all clean run_cg run_gtk run_img

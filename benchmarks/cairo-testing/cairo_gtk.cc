#include <stdio.h>
#include <glib.h>

#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/eventbox.h>

#include "common_draw.h"

class GtkCanvas : public Gtk::EventBox 
{
public:
	GtkCanvas ()
		: Gtk::EventBox ()
		, tme (0)
		, cnt (0)
	{}

	bool idle_redraw () {
		queue_draw ();
		return true;
	}

protected:
	bool on_expose_event (GdkEventExpose*);

	void on_size_request (Gtk::Requisition* r) {
		Gtk::EventBox::on_size_request (r);
		r->width = 800;
		r->height = 600;
	}

private:
	double tme;
	uint64_t cnt;
};

bool
GtkCanvas::on_expose_event (GdkEventExpose* ev)
{
	 const int64_t start = g_get_monotonic_time ();

	 Cairo::RefPtr<Cairo::Context> ctx = get_window()->create_cairo_context ();
	 ctx->rectangle (ev->area.x, ev->area.y, ev->area.width, ev->area.height);
	 ctx->clip();

	 ctx->rectangle (ev->area.x, ev->area.y, ev->area.width, ev->area.height);
	 ctx->set_source_rgba (0.1, 0.1, 0.1, 1);
	 ctx->fill ();

	 common_draw (ctx->cobj(), 800, 600);

	 const int64_t end = g_get_monotonic_time ();
	 const int64_t elapsed = end - start;
	 tme += elapsed;
	 ++cnt;

	 char buf [128];
	 snprintf (buf, sizeof(buf), "avg: %8.3f ms cur: %.2f ms",
			 (tme / (double)cnt) / 1000.f,
			 elapsed / 1000.f);

	 ctx->move_to (10, 50);
	 ctx->set_source_rgb (0.9, 0.2, 0.2);
	 ctx->set_font_size (32);
	 cairo_show_text (ctx->cobj(), buf);

	return true;
}

int main (int argc, char** argv)
{
	Gtk::Main main (argc, argv);
	Gtk::Window window;
	GtkCanvas canvas;

	window.add (canvas);
	canvas.show();

	Glib::signal_idle().connect (sigc::mem_fun (canvas, &GtkCanvas::idle_redraw));

	Gtk::Main::run(window);
	return 0;
}

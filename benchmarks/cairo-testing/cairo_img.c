#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <cairo.h>

#include "common_draw.h"

void run_one (cairo_surface_t* surface)
{
	static double tme = 0;
	static int64_t cnt = 0;

	const int64_t start = g_get_monotonic_time ();
	cairo_t* cr = cairo_create (surface);

	cairo_rectangle (cr, 0, 0, 800, 600);
	cairo_set_source_rgba (cr, 0.1, 0.1, 0.1, 1);
	cairo_fill (cr);

	common_draw (cr, 800, 600);

	const int64_t end = g_get_monotonic_time ();

	const int64_t elapsed = end - start;
	tme += elapsed;
	++cnt;

	printf ("avg: %8.3f ms cur: %.2f ms\n",
			(tme / (double)cnt) / 1000.f,
			elapsed / 1000.f);
}

int main (int argc, char** argv)
{
	cairo_surface_t* s = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 800, 600);
	int i;
	for (i = 0; i < 100; ++i) {
		run_one (s);
	}
	cairo_surface_destroy (s);
	return 0;
}

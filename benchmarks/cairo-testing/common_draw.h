static void
common_draw (cairo_t* cr, int w, int h)
{
	int i;
	for (i = 0; i < 50; ++i) {
		double r = (random() % 65536) /65536.0;
		double g = (random() % 65536) /65536.0;
		double b = (random() % 65536) /65536.0;
		cairo_set_source_rgba (cr, r, g, b, 1);

		int rw = random () % (w/2);
		int rh = random () % (h/2);

		int x = random () % (w - rw);
		int y = random () % (h - rh);

		cairo_rectangle (cr, x, y, rw, rh);
		cairo_set_source_rgba (cr, r, g, b, 0.5);
		cairo_fill (cr);
	}

	cairo_set_line_width (cr, 2);
	cairo_move_to (cr, w/2, h/2);

	for (i = 0; i < 50; ++i) {
		int x = random () % w;
		int y = random () % h;

		double r = (random() % 65536) /65536.0;
		double g = (random() % 65536) /65536.0;
		double b = (random() % 65536) /65536.0;
		cairo_set_source_rgba (cr, r, g, b, 1);
		cairo_line_to (cr, x, y);
		cairo_stroke (cr);
		cairo_move_to (cr, x, y);
	}
}

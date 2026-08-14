
/* Function prototypes */
#include "tests.h"
#include "appdata.h"
#include "timing.h"
#include "callbacks.h"

gboolean
on_idle (gpointer data)
{
	AppData *appdata = NULL;
	appdata = (AppData *) data;

	/* remove this idle handle */
	g_source_remove (appdata->idle_id);
	appdata->idle_id = 0;

	/* record start time */
	appdata->time_start_all = get_time ();

	/* Perform test type loop */
	perform_test_type (appdata);

	return TRUE;
}

void
toggle_test_count (AppData * appdata)
{

	if (appdata->test_count > 0)
	{
		appdata->test_count--;
	}
	else
	{


		/* report time taken to test */
		add_test_info_time (appdata);
		g_source_remove (appdata->test_idle_id);

		/* jump away it only one test was selected */
		if (appdata->test_only_one)
		{
			appdata->test_type = 99;
		}
		else
		{
			appdata->test_type++;
			appdata->test_count = appdata->test_count_selected;
			appdata->test_state_data = 0;
		}

		perform_test_type (appdata);
	}
}


/**
 * Callback for gtkentry test.
 * @param data user data.
 */
gboolean
on_idle_gtkentry_test (gpointer data)
{

	AppData *appdata = NULL;
	appdata = (AppData *) data;

	if ((appdata->test_count % 2) != 0)
	{
		gtk_entry_set_text (GTK_ENTRY (appdata->entry_entrys),
				    "Test String");

	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY (appdata->entry_entrys),
				    "Longer test string");
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtkcombobox test.
 * @param data user data.
 */
gboolean
on_idle_gtkcombobox_test (gpointer data)
{

	AppData *appdata = NULL;
	appdata = (AppData *) data;

	if ((appdata->test_count % 2) != 0)
	{
		gtk_combo_box_popup (GTK_COMBO_BOX
				     (appdata->combobox_entrys));
		gtk_combo_box_set_active (GTK_COMBO_BOX
					  (appdata->combobox_entrys),
					  appdata->test_state_data);

	}
	else
	{
		gtk_combo_box_popdown (GTK_COMBO_BOX
				       (appdata->combobox_entrys));

		appdata->test_state_data++;
		if (appdata->test_state_data > 9)
		{
			appdata->test_state_data = 0;
		}
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtkcomboboxentry test.
 * @param data user data.
 */
gboolean
on_idle_gtkcomboboxentry_test (gpointer data)
{
	AppData *appdata = NULL;
	appdata = (AppData *) data;

	if ((appdata->test_count % 2) != 0)
	{
		gtk_combo_box_popup (GTK_COMBO_BOX
				     (appdata->comboboxentry_entrys));
		gtk_combo_box_set_active (GTK_COMBO_BOX
					  (appdata->comboboxentry_entrys),
					  appdata->test_state_data);

	}
	else
	{
		gtk_combo_box_popdown (GTK_COMBO_BOX
				       (appdata->comboboxentry_entrys));

		appdata->test_state_data++;
		if (appdata->test_state_data > 9)
		{
			appdata->test_state_data = 0;
		}
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtkspinbutton test.
 * @param data user data.
 */
gboolean
on_idle_gtkspinbutton_test (gpointer data)
{
	AppData *appdata = NULL;
	appdata = (AppData *) data;

	gtk_spin_button_spin (GTK_SPIN_BUTTON (appdata->spinbutton_entrys),
			      GTK_SPIN_STEP_FORWARD, 1);

	appdata->test_state_data++;
	if (appdata->test_state_data > 999)
	{
		appdata->test_state_data = 0;
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtkprogressbar test.
 * @param data user data.
 */
gboolean
on_idle_gtkprogressbar_test (gpointer data)
{
	AppData *appdata = NULL;
	appdata = (AppData *) data;

	gdouble progress = (1 - ((appdata->test_count % 100) / 100.0));
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR
				       (appdata->progressbar_entrys),
				       progress);

	appdata->test_state_data++;
	if (appdata->test_state_data > 999)
	{
		appdata->test_state_data = 0;
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtktogglebutton test.
 * @param data user data.
 */
gboolean
on_idle_gtktogglebutton_test (gpointer data)
{
	AppData *appdata = NULL;
	appdata = (AppData *) data;

	if ((appdata->test_count % 2) != 0)
	{
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
					      (appdata->togglebutton_buttons),
					      TRUE);
	}
	else
	{
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
					      (appdata->togglebutton_buttons),
					      FALSE);
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}

/**
 * Callback for gtkcheckbutton test.
 * @param data user data.
 */
gboolean
on_idle_gtkcheckbutton_test (gpointer data)
{
	AppData *appdata = NULL;
	appdata = (AppData *) data;

	if ((appdata->test_count % 2) != 0)
	{
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
					      (appdata->checkbutton_buttons),
					      TRUE);
	}
	else
	{
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
					      (appdata->checkbutton_buttons),
					      FALSE);
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}

/**
 * Callback for gtkradiobutton test.
 * @param data user data.
 */
gboolean
on_idle_gtkradiobutton_test (gpointer data)
{
	AppData *appdata = NULL;
	appdata = (AppData *) data;

	if ((appdata->test_count % 2) != 0)
	{
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
					      (appdata->
					       radiobutton_buttons_1), TRUE);
	}
	else
	{
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
					      (appdata->
					       radiobutton_buttons_2), TRUE);
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtktextview add text test.
 * @param data user data.
 */
gboolean
on_idle_gtktextview_addtext_test (gpointer data)
{
	AppData *appdata = NULL;
	appdata = (AppData *) data;

	GtkTextIter iter;
	gtk_text_buffer_get_end_iter (appdata->textview_text_buffer, &iter);
	gtk_text_buffer_insert (appdata->textview_text_buffer, &iter,
				"Future is Open. ", -1);

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtktexview scroll test.
 * @param data user data.
 */
gboolean
on_idle_gtktextview_scroll_test (gpointer data)
{

	AppData *appdata = NULL;
	appdata = (AppData *) data;

	GtkRange *range;
	gdouble before, after;

	range = GTK_RANGE (gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(appdata->scrolledwindow_text)));

	before = gtk_range_get_value (range);
	g_signal_emit_by_name (range, "move-slider",
			       appdata->textview_text_scroll_type);
	after = gtk_range_get_value (range);

	/* if movement didn't work, change direction */
	if (before == after)
	{
		appdata->textview_text_scroll_type =
			(appdata->textview_text_scroll_type ==
			 GTK_SCROLL_STEP_FORWARD) ? GTK_SCROLL_STEP_BACKWARD :
			GTK_SCROLL_STEP_FORWARD;
	}

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtkdrawingarea line test.
 * @param data user data.
 */
gboolean
on_idle_gtkdrawingarea_lines_test (gpointer data)
{

	AppData *appdata = NULL;
	appdata = (AppData *) data;

	int i = 0;

	/* create graphical context */
	appdata->graphical_context = gdk_cairo_create(gtk_widget_get_window(appdata->drawingarea_drawing));
	cairo_set_line_width (appdata->graphical_context, 0.5);


	/* drawing lines is so fast that we'll make 1000 in one loop */
	/* just remember to show this in results! */
	for (i = 0; i < 1000; i++)
	{

		set_random_drawing_color (appdata->graphical_context);

		GtkAllocation tmp; 
		gtk_widget_get_allocation(appdata->drawingarea_drawing, &tmp);
		gint x1 = g_random_int_range (0, tmp.width);
		gint x2 = g_random_int_range (0, tmp.width);
		gint y1 = g_random_int_range (0, tmp.height);
		gint y2 = g_random_int_range (0, tmp.height);

		cairo_move_to(appdata->graphical_context, x1, y1);
		cairo_line_to(appdata->graphical_context, x2, y2);
		cairo_stroke(appdata->graphical_context);
	}
	

	cairo_destroy(appdata->graphical_context);

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtkdrawingarea circle test.
 * @param data user data.
 */
gboolean
on_idle_gtkdrawingarea_circles_test (gpointer data)
{

	AppData *appdata = NULL;
	appdata = (AppData *) data;

	int i = 0;

	/* create graphical context */
	appdata->graphical_context = gdk_cairo_create(gtk_widget_get_window(appdata->drawingarea_drawing));
	cairo_set_line_width (appdata->graphical_context, 0.5);

	/* drawing circles is so fast that we'll make 1000 in one loop */
	/* just remember to show this in results! */
	GtkAllocation tmp; 
	gtk_widget_get_allocation(appdata->drawingarea_drawing, &tmp);
	for (i = 0; i < 1000; i++)
	{

		set_random_drawing_color (appdata->graphical_context);

		gint x = g_random_int_range (0, tmp.width);
		gint y = g_random_int_range (0, tmp.height);
		gint width = g_random_int_range (0, 100);
		gint height = g_random_int_range (0, 100);

		cairo_arc(appdata->graphical_context, x, y, (width < height ? width : height) / 2, 0, 2*3.14159265358979323846);
		cairo_stroke(appdata->graphical_context);

	}

	cairo_destroy(appdata->graphical_context);

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}



/**
 * Callback for gtkdrawingarea text test.
 * @param data user data.
 */
gboolean
on_idle_gtkdrawingarea_text_test (gpointer data)
{

	AppData *appdata = NULL;
	appdata = (AppData *) data;

	int i = 0;

	/* create graphical context */
	appdata->graphical_context = gdk_cairo_create(gtk_widget_get_window(appdata->drawingarea_drawing));
	

	PangoLayout *layout;
	PangoFontDescription *fontdesc;
	layout = gtk_widget_create_pango_layout (appdata->drawingarea_drawing,
						 "Future is Open.");
	fontdesc = pango_font_description_from_string ("Sans Bold 16");
	pango_layout_set_font_description (layout, fontdesc);

	GtkAllocation tmp; 
	gtk_widget_get_allocation(appdata->drawingarea_drawing, &tmp);
	/* drawing text is so fast that we'll make 100 in one loop */
	/* just remember to show this in results! */
	for (i = 0; i < 100; i++)
	{

		set_random_drawing_color (appdata->graphical_context);

		gint x = g_random_int_range (0, tmp.width);
		gint y = g_random_int_range (0, tmp.height);

		cairo_move_to(appdata->graphical_context, x, y);
		pango_cairo_show_layout (appdata->graphical_context, layout);

	}

	pango_font_description_free (fontdesc);
	g_object_unref (layout);

	cairo_destroy(appdata->graphical_context);

	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


/**
 * Callback for gtkdrawingarea pixbuf test.
 * @param data user data.
 */
gboolean
on_idle_gtkdrawingarea_pixbufs_test (gpointer data)
{

	AppData *appdata = NULL;
	appdata = (AppData *) data;

	int i = 0;
	appdata->graphical_context = gdk_cairo_create(gtk_widget_get_window(appdata->drawingarea_drawing));

	GtkAllocation tmp; 
	gtk_widget_get_allocation(appdata->drawingarea_drawing, &tmp);
	/* drawing pixbufs is so fast that we'll make 10 in one loop */
	/* just remember to show this in results! */
	for (i = 0; i < 10; i++)
	{

		gint x = g_random_int_range (0, tmp.width);
		gint y = g_random_int_range (0, tmp.height);
		gdk_cairo_set_source_pixbuf (appdata->graphical_context, appdata->pixbuf_drawing, x, y);
		cairo_paint (appdata->graphical_context);
	}

	cairo_destroy (appdata->graphical_context);
	/* Check if test counter is up */
	toggle_test_count (appdata);

	return TRUE;
}


#include <gtk/gtk.h>

#include "appdata.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "tests.h"
#include "timing.h"


/* Global AppData variable */
AppData *appdata;


void
perform_test_type (AppData * data)
{

	switch (data->test_type)
	{

	case 1:
		add_test_info (data, "GtkEntry");
		data->test_idle_id = g_idle_add (on_idle_gtkentry_test, data);
		break;

	case 2:
		add_test_info (data, "GtkComboBox");
		data->test_idle_id =
			g_idle_add (on_idle_gtkcombobox_test, data);
		break;

	case 3:
		add_test_info (data, "GtkComboBoxEntry");
		data->test_idle_id =
			g_idle_add (on_idle_gtkcomboboxentry_test, data);
		break;

	case 4:
		add_test_info (data, "GtkSpinButton");
		data->test_idle_id =
			g_idle_add (on_idle_gtkspinbutton_test, data);
		break;

	case 5:
		add_test_info (data, "GtkProgressBar");
		data->test_idle_id =
			g_idle_add (on_idle_gtkprogressbar_test, data);
		break;

	case 6:
		add_test_info (data, "GtkToggleButton");
		data->test_idle_id =
			g_idle_add (on_idle_gtktogglebutton_test, data);
		break;

	case 7:
		add_test_info (data, "GtkCheckButton");
		data->test_idle_id =
			g_idle_add (on_idle_gtkcheckbutton_test, data);
		break;

	case 8:
		add_test_info (data, "GtkRadioButton");
		data->test_idle_id =
			g_idle_add (on_idle_gtkradiobutton_test, data);
		break;

	case 9:
		add_test_info (data, "GtkTextView - Add text");
		data->test_idle_id =
			g_idle_add (on_idle_gtktextview_addtext_test, data);
		break;

	case 10:
		add_test_info (data, "GtkTextView - Scroll");
		data->test_idle_id =
			g_idle_add (on_idle_gtktextview_scroll_test, data);
		break;

	case 11:
		add_test_info (data, "GtkDrawingArea - Lines");
		data->test_idle_id =
			g_idle_add (on_idle_gtkdrawingarea_lines_test, data);
		break;

	case 12:
		add_test_info (data, "GtkDrawingArea - Circles");
		data->test_idle_id =
			g_idle_add (on_idle_gtkdrawingarea_circles_test,
				    data);
		break;

	case 13:
		add_test_info (data, "GtkDrawingArea - Text");
		data->test_idle_id =
			g_idle_add (on_idle_gtkdrawingarea_text_test, data);
		break;

	case 14:
		add_test_info (data, "GtkDrawingArea - Pixbufs");
		data->test_idle_id =
			g_idle_add (on_idle_gtkdrawingarea_pixbufs_test,
				    data);
		break;

	default:

		/* testing has ended */
		/* report end time */
		add_test_info_end (data);
		gtk_notebook_set_current_page (data->notebook_main, 0);
		if (appdata->scripted)
		{
			on_cleanup_and_exit();  /*test*/
		}
	}

	/* record start time for each test */
	data->time_start_test = get_time ();
}


void
on_button_start_clicked (GtkButton * button, gpointer user_data)
{

	gtk_notebook_set_current_page (appdata->notebook_main, 1);

	/* get test count */
	appdata->test_count_selected =
		gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON
						  (appdata->
						   spinbutton_count));
	appdata->test_count = appdata->test_count_selected;

	/* get test type */
	appdata->test_type =
		gtk_combo_box_get_active (GTK_COMBO_BOX
					  (appdata->combobox_testtype));
	if (appdata->test_type > 0)
	{
		appdata->test_only_one = TRUE;
	}
	else
	{
		appdata->test_only_one = FALSE;
		appdata->test_type = 1;
	}

	/* Add statup info */
	add_test_info_start (appdata);

	/* reset test widgets state */
	reset_test_widgets ();

	/* enable idle callback */
	appdata->idle_id = g_idle_add (on_idle, appdata);
}


void
on_cmdline_run_all ()
{
	gtk_notebook_set_current_page (appdata->notebook_main, 1);

	/* get test count */
	if (appdata->test_count_selected != DEFAULT_COUNT) {
		appdata->test_count_selected =
			gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON
			(appdata->
			spinbutton_count));
			appdata->test_count = appdata->test_count_selected;
	}

	/* get test type */
	appdata->test_type =
		gtk_combo_box_get_active (GTK_COMBO_BOX
		(appdata->combobox_testtype));
	if (appdata->test_type > 0)
	{
		appdata->test_only_one = TRUE;
	}
	else
	{
		appdata->test_only_one = FALSE;
		appdata->test_type = 1;
	}

	/* Add statup info */
	add_test_info_start (appdata);

	/* reset test widgets state */
	reset_test_widgets ();

	/* enable idle callback */
	appdata->idle_id = g_idle_add (on_idle, appdata);
}


void
on_cmdline_help () {
	g_print("Usage: gtkperf [OPTION]...\n");
	g_print("GtkPerf is an application designed to test GTK+ performance.\n");
	g_print("\n");
	g_print("Options:\n");
	g_print("  -h,   --help          display this help and exit\n");
	g_print("  -a,   --automatic     start the testing automatically and exit when ready\n");
	g_print("  -c,   --count=COUNT   used testing count (default 100)\n");
	g_print("\n");
}


void
on_cmdline_count (char *optarg)
{
	appdata->test_count_selected = atoi(optarg);
}


/* Initialize appdata */
void
setup_appdata(AppData * appdata_in)
{

	appdata = (AppData *) appdata_in;

	appdata->textview_text_scroll_type = GTK_SCROLL_STEP_FORWARD;
	appdata->idle_id = 0;
	appdata->test_idle_id = 0;
	appdata->test_count = 0;
	appdata->test_count_selected = DEFAULT_COUNT;
	appdata->test_type = 0;
	appdata->test_state_data = 0;
	appdata->test_only_one = FALSE;
}


/* Initialize UI */
void
on_window_main_show (AppData * appdata_in)
{

	appdata = (AppData *) appdata_in;

	/* Getting buffers of text views */
	appdata->textview_text_buffer =
		gtk_text_view_get_buffer (GTK_TEXT_VIEW
					  (appdata->textview_text));
	appdata->textview_info_buffer =
		gtk_text_view_get_buffer (GTK_TEXT_VIEW
					  (appdata->textview_info));

	/* setup widgets */
	setup_widgets ();

	gtk_notebook_set_current_page (appdata->notebook_main, 0);

	gtk_spin_button_set_value (GTK_SPIN_BUTTON
				   (appdata->spinbutton_count),
				   appdata->test_count_selected);

	/* Set help text */
	gtk_text_buffer_set_text (gtk_text_view_get_buffer
				  (GTK_TEXT_VIEW (appdata->textview_help)),
				  _
				  ("GtkPerf - \xC2\xA9 2005 Kaj Gr\303\266nholm\n==========\nGtkPerf is "
				   "an application designed to test GTK+ performance. The point is to "
				   "create common testing platform to run predefined GTK+ widgets "
				   "(opening  comboboxes, toggling buttons, scrolling text etc.) and this "
				   "way define the speed of device/platform.\n\n\nTests\n==========\n\n"
				   "The tests are separate from each other with the same main logic: "
				   "making single test operation (opening combo box, drawing n circles, "
				   "etc.) and waiting for that to get processed are returned to g_idle. "
				   "So every test is jumping between test function and g_idle as fast as "
				   "possible. \n\nThese tests are provided (in 0.30).\n\n"
				   "GtkEntry (on_idle_gtkentry_test)\n----------\n"
				   "Switches between \"Test String\" and \"Longer test string\" texts for "
				   "[count] times.\n\n\n"
				   "GtkComboBox (on_idle_gtkcombobox_test)\n----------\n"
				   "GtkComboBox contains 10 entrys \"Selection 1\"...\"Selection 10\". "
				   "This test opens and closes GtkComboBox [count] times while selecting "
				   "next entry.\n\n\n"
				   "GtkComboBoxEntry (on_idle_gtkcomboboxentry_test)\n----------\n"
				   "GtkComboBoxEntry contains 10 entrys \"Selection 1\"...\"Selection 10\". "
				   "This test opens and closes GtkComboBoxEntry [count] times while "
				   "selecting next entry.\n\n\n"
				   "GtkSpinButton (on_idle_gtkspinbutton_test)\n----------\n"
				   "GtkSpinButton value is increased with one [count] times. "
				   "When 1000 is reached, value is changed back to 0.\n\n\n"
				   "GtkProgressBar (on_idle_gtkprogressbar_test)\n-----\n"
				   "GtkProgressBar is increased with 1% [count] times. Whenever bar gets "
				   "full, its value is set to 0.\n\n\n"
				   "GtkToggleButton (on_idle_gtktogglebutton_test)\n----------\n"
				   "GtkToggleButton state is toggled between on/off [count] times.\n\n\n"
				   "GtkCheckButton (on_idle_gtkcheckbutton_test)\n----------\n"
				   "GtkCheckButton state is toggled between on/off [count] times.\n\n\n"
				   "GtkRadioButton (on_idle_gtkradiobutton_test)\n----------\n"
				   "Two GtkRadioButtons inside same group are witched to be selected "
				   "alternately [count] times.\n\n\n"
				   "GtkTextView - Add text (on_idle_gtktextview_addtext_test)\n----------\n"
				   "Text \"Future is Open. \" is appended to GtkTextView [count] times.\n\n\n"
				   "GtkTextView - Scroll (on_idle_gtktextview_scroll_test)\n----------\n"
				   "Scrolls the text added in earlier test GTK_SCROLL_STEP_FORWARD and when "
				   "end is reached GTK_SCROLL_STEP_BACKWARD for [count times.\n\n\n"
				   "GtkDrawingArea - Lines (on_idle_gtkdrawingarea_lines_test)\n----------\n"
				   "Draws random size and color lines to GtkDrawingArea for 1000*[count] "
				   "times.\n\n\n"
				   "GtkDrawingArea - Circles (on_idle_gtkdrawingarea_circles_test)\n----------\n"
				   "Draws random size and color circles to GtkDrawingArea for 1000*[count] "
				   "times.\n\n\n"
				   "GtkDrawingArea - Text (on_idle_gtkdrawingarea_text_test)\n----------\n"
				   "Draws random size and color \"Future is Open.\" strings with "
				   "PangoLayout to GtkDrawingArea for 100*[count] times. Font used is "
				   "\"Sans Bold 16\".\n\n\n"
				   "GtkDrawingArea - Pixbuf (on_idle_gtkdrawingarea_pixbufs_test)\n----------\n"
				   "Draws Duck.png to random place in GtkDrawingArea for 10*[count] "
				   "times.\n"), -1);
}


gboolean
on_cleanup_and_exit()
{
	g_print("Quitting..\n");
	gtk_main_quit();
	return FALSE;
}


gboolean
on_window_main_delete_event (GtkWidget * widget,
			     GdkEvent * event, gpointer user_data)
{
	return on_cleanup_and_exit();
}

void
setup_widgets ()
{

	/* Add strings to comboboxes */
	
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 2");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 3");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 4");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 5");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 6");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 7");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 8");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 9");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (appdata->combobox_entrys), 
				   "selection 10");
	
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 2");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 3");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 4");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 5");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 6");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 7");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 8");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 9");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT
				   (appdata->comboboxentry_entrys), 
				   "selection 10");
	
	gchar *filename = g_build_filename (PACKAGE_PIXMAPS_DIR,
					    "duck.png", NULL);
	appdata->pixbuf_drawing = gdk_pixbuf_new_from_file (filename, NULL);

	gtk_combo_box_set_active (GTK_COMBO_BOX (appdata->combobox_testtype),
				  0);

	/* create end mark to info textview */
	GtkTextIter iter;
	gtk_text_buffer_get_end_iter (appdata->textview_info_buffer, &iter);
	appdata->end_mark_info =
		gtk_text_buffer_create_mark (GTK_TEXT_BUFFER
					     (appdata->textview_info_buffer),
					     NULL, &iter, TRUE);

	/* add version info to statusbar */
	gtk_statusbar_push (GTK_STATUSBAR (appdata->statusbar_main), 0,
			    APP_VERSION);

}

/* Reset the stage of all testing widgets before starting the new test */
void
reset_test_widgets ()
{

	gtk_entry_set_text (GTK_ENTRY (appdata->entry_entrys), "");
	gtk_combo_box_set_active (GTK_COMBO_BOX
				  (appdata->comboboxentry_entrys), 0);
	gtk_combo_box_set_active (GTK_COMBO_BOX
				  (appdata->combobox_entrys), 0);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON
				   (appdata->spinbutton_entrys), 0);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR
				       (appdata->progressbar_entrys), 0.0);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
				      (appdata->togglebutton_buttons), FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
				      (appdata->checkbutton_buttons), FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
				      (appdata->radiobutton_buttons_1), TRUE);
	gtk_text_buffer_set_text (appdata->textview_text_buffer, "", 0);

}


void
set_random_drawing_color (cairo_t *cr)
{
	double r = g_random_double_range (0, 1);
	double g = g_random_double_range (0, 1);
	double b = g_random_double_range (0, 1);
	cairo_set_source_rgb(cr, r, g, b);
}

void
on_button_clear_clicked (GtkButton * button, gpointer user_data)
{
	gtk_text_buffer_set_text (appdata->textview_info_buffer, "", 0);
}

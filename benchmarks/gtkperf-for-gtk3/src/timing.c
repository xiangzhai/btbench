#include <glib.h>
#include <glib/gprintf.h>
#include <time.h>
#include <sys/time.h>

/* Function prototypes */
#include "timing.h"
#include "appdata.h"

/**
 * Timing code.
 */
double
get_time (void)
{
	struct timeval tv;

	gettimeofday (&tv, NULL);
	return (double) tv.tv_sec + (double) tv.tv_usec / 1E6;
}

void
add_test_info (AppData * appdata, gchar * testname)
{

	/* TODO: get testname from combo instead */

	GtkTextIter iter;
	gtk_text_buffer_get_end_iter (appdata->textview_info_buffer, &iter);
	gtk_text_buffer_insert (appdata->textview_info_buffer, &iter,
				testname, -1);
	gtk_text_buffer_insert (appdata->textview_info_buffer, &iter, " - ",
				-1);

	g_print ("%s - ", testname);


	switch (appdata->test_type)
	{

	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		gtk_notebook_set_current_page (appdata->notebook_main, 1);
		gtk_label_set_text (GTK_LABEL (appdata->label_entrys),
				    testname);
		break;

	case 6:
	case 7:
	case 8:
		gtk_notebook_set_current_page (appdata->notebook_main, 2);
		gtk_label_set_text (GTK_LABEL (appdata->label_buttons),
				    testname);
		break;

	case 9:
	case 10:
		gtk_notebook_set_current_page (appdata->notebook_main, 3);
		gtk_label_set_text (GTK_LABEL (appdata->label_text),
				    testname);
		break;

	case 11:
	case 12:
	case 13:
	case 14:
		gtk_notebook_set_current_page (appdata->notebook_main, 4);
		gtk_label_set_text (GTK_LABEL (appdata->label_drawing),
				    testname);
		break;

	case 15:
	default:
		gtk_notebook_set_current_page (appdata->notebook_main, 5);
		gtk_label_set_text (GTK_LABEL (appdata->label_text),
				    testname);
		break;

	}
}


void
add_test_info_time (AppData * appdata)
{

	gchar *timestring;
	timestring =
		g_strdup_printf ("time: %5.2f\n",
				 (get_time () - appdata->time_start_test));

	GtkTextIter iter;
	gtk_text_buffer_get_end_iter (appdata->textview_info_buffer, &iter);
	gtk_text_buffer_insert (appdata->textview_info_buffer, &iter,
				timestring, -1);

	g_printf ("%s", timestring);

}


void
add_test_info_end (AppData * appdata)
{

	gchar *timestring;
	timestring =
		g_strdup_printf (" --- \nTotal time: %5.2f\n\n",
				 (get_time () - appdata->time_start_all));

	GtkTextIter iter;
	gtk_text_buffer_get_end_iter (appdata->textview_info_buffer, &iter);
	gtk_text_buffer_insert (appdata->textview_info_buffer, &iter,
				timestring, -1);

	/* scroll to end of the text view */
	gtk_text_buffer_get_end_iter (appdata->textview_info_buffer, &iter);
	gtk_text_buffer_move_mark (GTK_TEXT_BUFFER
				   (appdata->textview_info_buffer),
				   appdata->end_mark_info, &iter);
	gtk_text_view_scroll_mark_onscreen (GTK_TEXT_VIEW
					    (appdata->textview_info),
					    appdata->end_mark_info);

	/* add ending info to statusbar */
	gtk_statusbar_push (GTK_STATUSBAR (appdata->statusbar_main), 0,
			    " Test Finished");

	g_printf ("%s", timestring);

}

void
add_test_info_start (AppData * appdata)
{

	gchar *timestring;
	time_t timer;
	time (&timer);
	timestring =
		g_strdup_printf ("%s - Starting testing: %s\n",
				APP_VERSION,
				asctime (localtime (&timer)));

	GtkTextIter iter;
	gtk_text_buffer_get_end_iter (appdata->textview_info_buffer, &iter);
	gtk_text_buffer_insert (appdata->textview_info_buffer, &iter,
				timestring, -1);

	/* add running info to statusbar */
	gtk_statusbar_push (GTK_STATUSBAR (appdata->statusbar_main), 0,
			    " Running tests...");

	g_printf ("%s", timestring);
}

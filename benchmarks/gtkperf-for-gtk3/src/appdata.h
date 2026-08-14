/* Maemo version or not? */
//#define HILDONIZED

#include <gtk/gtk.h>
#include <cairo.h>
#include <gdk/gdkcairo.h>


#ifdef HILDONIZED
#include <hildon-widgets/hildon-app.h>
#include <hildon-widgets/hildon-appview.h>
#endif

/* Application version info */
#define APP_VERSION "GtkPerf 0.40"

/* Default test count */
#define DEFAULT_COUNT 100

/* D-BUS service name */
#define APPLICATION_DBUS_SERVICE "gtkperf"

#ifndef APPDATA_H
#define APPDATA_H

#ifdef HAVE_CONFIG
#include <config.h>
#endif

/*
  Application data
*/
typedef struct _AppData AppData;
struct _AppData
{



#ifdef HILDONIZED
	HildonApp *app;
	HildonAppView *window_main;
#else
	GtkWidget *window_main;
#endif

	GtkNotebook *notebook_main;
	GtkWidget *combobox_testtype;
	GtkWidget *statusbar_main;
	GtkWidget *spinbutton_count;
	GtkWidget *textview_info;
	GtkTextBuffer *textview_info_buffer;
	GtkTextMark *end_mark_info;
	GtkWidget *textview_help;

	GtkWidget *label_entrys;
	GtkWidget *entry_entrys;
	GtkWidget *combobox_entrys;
	GtkWidget *comboboxentry_entrys;
	GtkWidget *spinbutton_entrys;
	GtkWidget *progressbar_entrys;

	GtkWidget *label_buttons;
	GtkWidget *togglebutton_buttons;
	GtkWidget *checkbutton_buttons;
	GtkWidget *radiobutton_buttons_1;
	GtkWidget *radiobutton_buttons_2;

	GtkWidget *label_text;
	GtkWidget *textview_text;
	GtkTextBuffer *textview_text_buffer;
	GtkWidget *scrolledwindow_text;

	GtkWidget *label_drawing;
	GtkWidget *drawingarea_drawing;
	GdkPixbuf *pixbuf_drawing;
	cairo_t *graphical_context;
	GdkColor current_color;

	GtkScrollType textview_text_scroll_type;

	guint idle_id;
	guint test_idle_id;
	double time_start_all;
	double time_start_test;
	int test_count;
	int test_count_selected;
	int test_type;
	int test_state_data;

	gboolean test_only_one;
	gboolean scripted;
};

#endif /* APPDATA_H */

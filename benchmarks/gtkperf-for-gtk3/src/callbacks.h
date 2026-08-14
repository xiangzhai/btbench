#include <gtk/gtk.h>

#include "appdata.h"

/* function prototypes */
void reset_test_widgets ();
void set_random_drawing_color ();
void perform_test_type (AppData * data);
void setup_widgets ();


void on_button_start_clicked (GtkButton * button, gpointer user_data);
void on_cmdline_run_all ();
void on_cmdline_help () ;
void on_cmdline_count (char *optarg) ;
void on_window_main_show (AppData * data);

gboolean
on_window_main_destroy_event (GtkWidget * widget,
			      GdkEvent * event, gpointer user_data);
gboolean
on_cleanup_and_exit();

gboolean
on_window_main_delete_event (GtkWidget * widget,
			     GdkEvent * event, gpointer user_data);

void on_button_clear_clicked (GtkButton * button, gpointer user_data);

#include <gtk/gtk.h>

#include "appdata.h"

void toggle_test_count (AppData * appdata);

gboolean on_idle (gpointer data);
gboolean on_idle_gtkentry_test (gpointer data);
gboolean on_idle_gtkcombobox_test (gpointer data);
gboolean on_idle_gtkcomboboxentry_test (gpointer data);
gboolean on_idle_gtkspinbutton_test (gpointer data);
gboolean on_idle_gtkprogressbar_test (gpointer data);
gboolean on_idle_gtktogglebutton_test (gpointer data);
gboolean on_idle_gtkcheckbutton_test (gpointer data);
gboolean on_idle_gtkradiobutton_test (gpointer data);
gboolean on_idle_gtktextview_addtext_test (gpointer data);
gboolean on_idle_gtktextview_scroll_test (gpointer data);
gboolean on_idle_gtkdrawingarea_lines_test (gpointer data);
gboolean on_idle_gtkdrawingarea_circles_test (gpointer data);
gboolean on_idle_gtkdrawingarea_text_test (gpointer data);
gboolean on_idle_gtkdrawingarea_pixbufs_test (gpointer data);

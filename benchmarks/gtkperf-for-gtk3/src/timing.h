#include <gtk/gtk.h>

#include "appdata.h"

/* function prototypes */

double get_time (void);
void add_test_info (AppData * appdata, gchar * testname);
void add_test_info_start (AppData * appdata);
void add_test_info_time (AppData * appdata);
void add_test_info_end (AppData * appdata);

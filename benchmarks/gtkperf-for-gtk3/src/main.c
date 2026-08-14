

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#ifdef HILDONIZED
#include <libosso.h>
#endif

#include <getopt.h>

#include "interface.h"
#include "support.h"
#include "callbacks.h"
#include "appdata.h"

int
main (int argc, char **argv)
{

#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	AppData *appdata;
	appdata = g_new0 (AppData, 1);

	gtk_init (&argc, &argv);
	appdata->scripted=FALSE;
	appdata->test_count_selected = DEFAULT_COUNT;

#ifdef HILDONIZED
	/* Initialize Maemo application */
	
    osso_context = osso_initialize(
        APPLICATION_DBUS_SERVICE, "0.1", TRUE, NULL);

    if (osso_context == NULL)
    {
        return OSSO_ERROR;
    }
	
#endif
	
	add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");


setup_appdata(appdata);


	int c;
	int digit_optind = 0;

	while (1) {

		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"help", 0, 0, 0},
			{"automatic", 0, 0, 0},
			{"count", 1, 0, 0},
			{0, 0, 0, 0}
		};
		c = getopt_long (argc, argv, "hac:",
			long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {

			case 0:

				if (option_index==0) {
					on_cmdline_help ();
					exit(0);
				}
				if (option_index==1) {
					appdata->scripted = TRUE;
				}
				if (option_index==2) {
					on_cmdline_count(optarg);
				}

				/* Debug code
				g_printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
					g_printf ("\n");
				*/

				break;

			case 'a':
				appdata->scripted = TRUE;
				break;

			case 'c':
				on_cmdline_count(optarg);
				break;

			default:
			case 'h':
				on_cmdline_help ();
				exit(0);
				break;

				/* Debug code 
				printf ("?? getopt returned character code 0%o ??\n", c);
				*/
		}
	}

	if (optind < argc) {
		printf ("non-option ARGV-elements: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
			printf ("\n");
	}

	
	appdata = create_window_main (appdata);
	gtk_widget_show (appdata->window_main);
	on_window_main_show (appdata);

	/* run automatic test */
	if (appdata->scripted == TRUE)
	{
		on_cmdline_run_all();
	}

	gtk_main ();
	return 0;
}

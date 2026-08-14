#include <stdio.h>
#include <stdlib.h>

#import <Cocoa/Cocoa.h>

#include <cairo/cairo.h>
#include <cairo-quartz.h>
#include <glib.h>

#include "common_draw.h"

struct appdata_t {
	id window;
	cairo_surface_t* surface;
};

static void makeAppMenu (void) {
	id menubar = [[NSMenu new] autorelease];
	id appMenuItem = [[NSMenuItem new] autorelease];
	[menubar addItem:appMenuItem];

	[NSApp setMainMenu:menubar];

	id appMenu = [[NSMenu new] autorelease];
	[appMenu addItemWithTitle:@"Quit" action:@selector(terminate:) keyEquivalent:@"q"];
	[appMenuItem setSubmenu:appMenu];
}

static void osx_loop (CFRunLoopTimerRef timer, void *data) {
	struct appdata_t* d = (struct appdata_t*) data;

	static double tme = 0;
	static int64_t cnt = 0;

	const int64_t start = g_get_monotonic_time ();
	
	cairo_t* cr = cairo_create (d->surface);

	cairo_rectangle (cr, 0, 0, 800, 600);
	cairo_set_source_rgba (cr, 0.1, 0.1, 0.1, 1);
	cairo_fill (cr);

	common_draw (cr, 800, 600);

	const int64_t end = g_get_monotonic_time ();

	const int64_t elapsed = end - start;
	tme += elapsed;
	++cnt;

	char buf [128];
	snprintf (buf, sizeof(buf), "avg: %8.3f ms cur: %.2f ms",
			(tme / (double)cnt) / 1000.f,
			elapsed / 1000.f);

	cairo_move_to (cr, 10, 50);
	cairo_set_source_rgb (cr, 0.9, 0.2, 0.2);
	cairo_set_font_size (cr, 32);
	cairo_show_text (cr, buf);

	cairo_destroy (cr);

	[[NSGraphicsContext currentContext] flushGraphics];
#ifdef TIME_PROFILE
	const int64_t t3 = g_get_monotonic_time ();
	printf ("T: %f ms  %f ms\n", (end - start) / 1000.f,  (t3 - end) / 1000.f);
#endif
}

static void
run_loop_observer_callback (CFRunLoopObserverRef observer, CFRunLoopActivity activity, void* data)
{
	struct appdata_t* d = (struct appdata_t*) data;
	if (activity == kCFRunLoopBeforeWaiting) {
		osx_loop (NULL, data);
		//[d->window displayIfNeeded];
	}
}


int main (int argc, char** argv)
{
	[NSAutoreleasePool new];
	[NSApplication sharedApplication];
	makeAppMenu ();
	int width = 800;
	int height = 600;

	const char *title = "Cairo Test";
	NSString* titleString = [[NSString alloc]
		initWithBytes:title
		length:strlen(title)
		encoding:NSUTF8StringEncoding];

	NSRect frame = NSMakeRect(0, 0, width, height);
	NSUInteger style = NSClosableWindowMask | NSTitledWindowMask;

	id window = [[[NSWindow alloc]
		initWithContentRect:frame
			  styleMask:style
			    backing:NSBackingStoreBuffered
			      defer:NO
			] retain];

	if (window == nil) {
		return -1;
	}

	[window setTitle:titleString];
	[window makeKeyAndOrderFront:window];

	[NSApp activateIgnoringOtherApps:YES];
	[window setIsVisible:YES];

	CGContextRef cg_context = [[NSGraphicsContext currentContext] graphicsPort];
	printf ("Flipped? %d\n", [[NSGraphicsContext currentContext] isFlipped]);
#if 1
	CGContextTranslateCTM (cg_context, 0.0, height);
	CGContextScaleCTM (cg_context, 1.0, -1.0);
#endif
	cairo_surface_t* surface = cairo_quartz_surface_create_for_cg_context (cg_context, width, height);

	struct appdata_t appdata;
	appdata.window = window;
	appdata.surface = surface;
	void* data = (void*) &appdata;

	CFRunLoopRef runLoop = CFRunLoopGetCurrent();
#if 1
	CFRunLoopTimerContext context = {0, data, NULL, NULL, 0};
	CFRunLoopTimerRef timer = CFRunLoopTimerCreate (kCFAllocatorDefault, 0, 1.0/25.0, 0, 0, &osx_loop, &context);
	CFRunLoopAddTimer(runLoop, timer, kCFRunLoopCommonModes);
#else
	CFRunLoopObserverContext context = {0, data, NULL, NULL, 0};
	CFRunLoopObserverRef obs = CFRunLoopObserverCreate (NULL, /* default allocator */
			kCFRunLoopAllActivities,
			true, /* repeats: not one-shot */
			0, /* order (priority) */
			run_loop_observer_callback,
			&context);
	CFRunLoopAddObserver(runLoop, obs, kCFRunLoopCommonModes);
#endif

	[NSApp run];

	[NSAutoreleasePool release];
	return 0;
}

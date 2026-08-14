## Process this file with automake to produce Makefile.in
## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

SUBDIRS = intl po src pixmaps

gtkperfdocdir = ${prefix}/doc/gtkperf
gtkperfdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	TODO

EXTRA_DIST = $(gtkperfdoc_DATA)

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done


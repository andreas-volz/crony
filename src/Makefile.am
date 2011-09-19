## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(EFL_CFLAGS) \
	$(SIGC_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = \
	libcrony.la

libcrony_la_SOURCES = \
	Cron.cpp     \
	CronTab.cpp     \
	DateTime.cpp     \
	CronExceptions.cpp     \
	stringUtil.h

libcrony_la_LIBADD = \
	$(SIGC_LIBS)

libcrony_la_CXXFLAGS = \
	-I../include


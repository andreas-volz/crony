## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(EFL_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = crony

crony_SOURCES = \
	main.cpp  \
	DateTime.cpp  \
	DateTime.h  \
	Cron.cpp  \
	Cron.h  \
	CronTab.cpp  \
	CronTab.h

crony_LDFLAGS = 

crony_LDADD = \
	$(EFL_LIBS)


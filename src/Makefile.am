## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	$(EFL_CFLAGS) \
	$(LOG4CXX_CFLAGS)

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
	$(LOG4CXX_LIBS)

libcrony_la_CXXFLAGS =    \
	-I../include


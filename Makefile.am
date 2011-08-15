## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src \
	include

cronydocdir = ${prefix}/doc/kidclock
cronydoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(cronydoc_DATA)

ACLOCAL_AMFLAGS = -I m4

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(cronydocdir)

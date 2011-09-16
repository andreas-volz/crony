dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(crony, 0.1)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC






AM_PROG_LIBTOOL






PKG_CHECK_MODULES(UNIT, cppunit)
PKG_CHECK_MODULES(SIGC, sigc++-2.0)
AC_OUTPUT([
Makefile
examples/Makefile
examples/basic/Makefile
include/Makefile
include/crony/Makefile
src/Makefile
test/Makefile
test/unit/Makefile
crony.pc
crony-uninstalled.pc
])

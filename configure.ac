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


#dnl Set PACKAGE SOURCE DIR in config.h.
packagesrcdir=`cd $srcdir && pwd`

#dnl Set PACKAGE PREFIX
if test "x${prefix}" = "xNONE"; then
  packageprefix=${ac_default_prefix}
else
  packageprefix=${prefix}
fi

#dnl Set PACKAGE DIRS in config.h
packagedatadir=share/${PACKAGE}
packagedocdir=doc/${PACKAGE}

#dnl Subst PACKAGE_DATA_DIR.
NO_PREFIX_PACKAGE_DATA_DIR="${packagedatadir}"
AC_SUBST(NO_PREFIX_PACKAGE_DATA_DIR)
PACKAGE_DATA_DIR="${packageprefix}/${packagedatadir}"
AC_SUBST(PACKAGE_DATA_DIR)

dnl Subst PACKAGE_DOC_DIR.
NO_PREFIX_PACKAGE_DOC_DIR="${packagedocdir}"
AC_SUBST(NO_PREFIX_PACKAGE_DOC_DIR)
PACKAGE_DOC_DIR="${packageprefix}/${packagedocdir}"
AC_SUBST(PACKAGE_DOC_DIR)

AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${packageprefix}/${packagedatadir}","")
AC_DEFINE_UNQUOTED(SYSTEM_DATA_DIR, "${packageprefix}/${systemdatadir}","")
AC_DEFINE_UNQUOTED(PACKAGE_DOC_DIR, "${packageprefix}/${packagedocdir}","")
AC_DEFINE_UNQUOTED(PACKAGE_SOURCE_DIR, "${packagesrcdir}","")


AM_PROG_LIBTOOL

dnl Check for option to enable logging
AC_MSG_CHECKING(whether to enable logging)
AC_ARG_ENABLE(logging,
        [  --enable-logging=[no/yes]        enables logging build (default=yes)],,
                 enable_logging=yes)

if [ ! test "$enable_logging" != "yes"]; then
  AC_DEFINE(HAVE_LOGGING, 1, [Define to enable logging build])
  AC_MSG_RESULT(yes)
  PKG_CHECK_MODULES([LOG4CXX], liblog4cxx,
        AC_DEFINE(HAVE_LOG4CXX, 1, [Define to enable logging build]),
        AC_DEFINE(HAVE_LOG4CXX, 0, [Define to enable logging build])
  )
else
  AC_DEFINE(HAVE_LOG4CXX, 0, [Define to enable logging build])
  AC_MSG_RESULT(no)
fi


PKG_CHECK_MODULES(UNIT, cppunit)
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


bin_PROGRAMS = \
	UnitTest

UnitTest_SOURCES = \
	CronTest.cpp\
	CronTest.h \
	TestMain.cpp \
	DateTimeTest.cpp \
	DateTimeTest.h \
	CronTabTest.cpp \
	CronTabTest.h

UnitTest_LDFLAGS = \
	../../src/libcrony.la

UnitTest_LDADD = \
	$(UNIT_LIBS)\
	$(LOG4CXX_LIBS)

UnitTest_CXXFLAGS = \
	-I../../include

AM_CPPFLAGS = \
	$(UNIT_CFLAGS)\
	$(LOG4CXX_CFLAGS)

## File created by the gnome-build tools


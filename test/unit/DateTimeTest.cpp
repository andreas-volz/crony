#include "DateTimeTest.h"

using namespace std;
using namespace crony;

CPPUNIT_TEST_SUITE_REGISTRATION (DateTimeTest);

void DateTimeTest::setUp (void)
{

}

void DateTimeTest::tearDown (void)
{
  
}

void DateTimeTest::test1 (void)
{
  crony::DateTime dtReference;
  std::ostringstream test;
  
  dtReference.setYear (2010 - DateTime::YearShift);
  dtReference.setMonth (DateTime::April);
  dtReference.setDayOfMonth (13);
  dtReference.setHours (11);
  dtReference.setMinutes (10);
  dtReference.setSeconds (0);

  test << dtReference;
  
  CPPUNIT_ASSERT (test.str ().size () != 0);
}


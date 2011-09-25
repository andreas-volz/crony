#include "DateTimeTest.h"

using namespace std;
using namespace crony;

CPPUNIT_TEST_SUITE_REGISTRATION (DateTimeTest);

void DateTimeTest::setUp ()
{

}

void DateTimeTest::tearDown ()
{
  
}

void DateTimeTest::test1 ()
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

void DateTimeTest::test2 ()
{
  crony::DateTime dtReference;
  
  dtReference.setYear (2010 - DateTime::YearShift);
  dtReference.setMonth (DateTime::April);
  dtReference.setDayOfMonth (13);
  dtReference.setHours (11);
  dtReference.setMinutes (10);
  dtReference.setSeconds (0);

  crony::DateTime dtReference2 (dtReference);
  
  dtReference2.setSeconds (dtReference.getSeconds () + 1);

  double result = dtReference2 - dtReference;

  CPPUNIT_ASSERT_EQUAL (1, (int) result);
}

void DateTimeTest::test3 ()
{
  crony::DateTime dtReference;
  
  dtReference.setYear (2010 - DateTime::YearShift);
  dtReference.setMonth (DateTime::April);
  dtReference.setDayOfMonth (13);
  dtReference.setHours (11);
  dtReference.setMinutes (10);
  dtReference.setSeconds (0);

  crony::DateTime dtReference2 (dtReference);
  
  dtReference2.setSeconds (dtReference.getSeconds () + 1);

  CPPUNIT_ASSERT (dtReference < dtReference2);
}

void DateTimeTest::test4 ()
{
  crony::DateTime dtReference;
  
  dtReference.setYear (2010 - DateTime::YearShift);
  dtReference.setMonth (DateTime::April);
  dtReference.setDayOfMonth (13);
  dtReference.setHours (11);
  dtReference.setMinutes (10);
  dtReference.setSeconds (0);

  crony::DateTime dtReference2 (dtReference);
  
  dtReference2.setSeconds (dtReference.getSeconds () + 1);

  CPPUNIT_ASSERT (dtReference2 > dtReference);
}

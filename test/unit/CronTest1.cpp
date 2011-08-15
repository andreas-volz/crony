#include "CronTest1.h"

CPPUNIT_TEST_SUITE_REGISTRATION (CronTest1);

void CronTest1::setUp (void)
{
}

void CronTest1::tearDown (void)
{
  
}

void CronTest1::myTest (void)
{
  CPPUNIT_ASSERT (true);
  CPPUNIT_ASSERT_EQUAL (2, 1);
}

void CronTest1::myTest2 (void)
{
  CPPUNIT_ASSERT (true);
  CPPUNIT_ASSERT_EQUAL (1, 1);
}


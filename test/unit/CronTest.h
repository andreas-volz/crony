#ifndef CRON_TEST_H
#define CRON_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// STD
#include <string.h>

// local
#include "crony/Cron.h"

class CronTest : public CPPUNIT_NS::TestFixture
{  
  CPPUNIT_TEST_SUITE (CronTest);

  // hit next year in future
  CPPUNIT_TEST (test1);

  // hit next month in future
  CPPUNIT_TEST (test2);

  // hit next day of month in future
  CPPUNIT_TEST (test3);

  // hit next dayofweek in future
  CPPUNIT_TEST (test4);

  // hit next hour in future
  CPPUNIT_TEST (test5);

  // hit next minute in future
  CPPUNIT_TEST (test6);

  // hit next year, month, day of month, hour and minute in future
  CPPUNIT_TEST (test7);

  // don't hit in yet started minute
  CPPUNIT_TEST (test8);

  // hit next hour, because minutes in past
  CPPUNIT_TEST (test9);

  // hit next day, because hours in past
  CPPUNIT_TEST (test10);

  // hit next month, because dayofmonth in past
  CPPUNIT_TEST (test11);

  // hit next week, because dayofweek in past
  CPPUNIT_TEST (test12);

  // hit next year, because month in past
  CPPUNIT_TEST (test13);

  // don't hit anything, because year in past
  CPPUNIT_TEST (test14);

  // hit next dayofweek (at month border, dayofweek in locale past)
  CPPUNIT_TEST (test15);

  // hit next dayofweek (at month border; dayofweek in locale future)
  CPPUNIT_TEST (test16);

  // hit next dayofweek (at year border, dayofweek in locale past)
  CPPUNIT_TEST (test17);

  // hit next dayofweek (at year border; dayofweek in locale future)
  CPPUNIT_TEST (test18);

  // hit each minute
  CPPUNIT_TEST (test19);

  // hit next year // TODO: same as test1?
  CPPUNIT_TEST (test20);

  // TODO: variant: add/subtract two instead of one (induktion...)...
  
  CPPUNIT_TEST_SUITE_END ();

public:
  void setUp ();
  void tearDown ();

protected:
  void test1 ();
  void test2 ();
  void test3 ();
  void test4 ();
  void test5 ();
  void test6 ();
  void test7 ();
  void test8 ();
  void test9 ();
  void test10 ();
  void test11 ();
  void test12 ();
  void test13 ();
  void test14 ();
  void test15 ();
  void test16 ();
  void test17 ();
  void test18 ();
  void test19 ();
  void test20 ();

private:
  crony::DateTime mdtReference;
};

#endif // CRON_TEST_H


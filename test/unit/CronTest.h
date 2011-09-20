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

  // hit one year in future
  CPPUNIT_TEST (test1);

  // hit one month in future
  CPPUNIT_TEST (test2);

  // hit one day of month in future
  CPPUNIT_TEST (test3);

  // hit  one dayofweek in future
  // FIXME
  //CPPUNIT_TEST (test4);

  // hit one hour in future
  CPPUNIT_TEST (test5);

  // hit one minute in future
  CPPUNIT_TEST (test6);

  // hit one year, month, day of month, hour and minute in future
  CPPUNIT_TEST (test7);

  // don't hit in yet started minute
  CPPUNIT_TEST (test8);

  // don't hit anything, because minutes in past
  CPPUNIT_TEST (test9);

  // don't hit anything, because hours in past
  CPPUNIT_TEST (test10);

  // don't hit anything, because dayofmonth in past
  CPPUNIT_TEST (test11);

  // don't hit anything, because dayofweek in past
  //CPPUNIT_TEST (test12);

  // don't hit anything, because month in past
  CPPUNIT_TEST (test13);

  // don't hit anything, because year in past
  CPPUNIT_TEST (test14);
  
  CPPUNIT_TEST_SUITE_END ();

public:
  void setUp (void);
  void tearDown (void);

protected:
  void test1 (void);
  void test2 (void);
  void test3 (void);
  void test4 (void);
  void test5 (void);
  void test6 (void);
  void test7 (void);
  void test8 (void);
  void test9 (void);
  void test10 (void);
  void test11 (void);
  //void test12 (void);
  void test13 (void);
  void test14 (void);

private:
  crony::DateTime mdtReference;
};

#endif // CRON_TEST_H


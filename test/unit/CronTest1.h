#ifndef CRONTEST1_H
#define CRONTEST1_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// STD
#include <string.h>

// local
#include "crony/Cron.h"

using namespace std;

class CronTest1 : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE (CronTest1);

  // hit one year in future
  CPPUNIT_TEST (test1);

  // hit one month in future
  CPPUNIT_TEST (test2);

  // hit one day of month in future
  CPPUNIT_TEST (test3);

  // hit  one day in week in future
  // FIXME
  //CPPUNIT_TEST (test4);

  // hit one hour in future
  CPPUNIT_TEST (test5);

  // hit one minute in future
  CPPUNIT_TEST (test6);

  // hit one year, month, day of month, hour and minute in future
  CPPUNIT_TEST (test7);
  
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

private:
  DateTime mdtReference;
};

#endif // CRONTEST1_H


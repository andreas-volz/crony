#ifndef DATE_TIME_TEST_H
#define DATE_TIME_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// STD
#include <string.h>

// local
#include "crony/DateTime.h"

class DateTimeTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE (DateTimeTest);

  // define a simple date and test << operator
  CPPUNIT_TEST (test1);

  // test - operator
  CPPUNIT_TEST (test2);

  CPPUNIT_TEST_SUITE_END ();

public:
  void setUp (void);
  void tearDown (void);

protected:
  void test1 (void);
  void test2 (void);

private:
  
};

#endif // DATE_TIME_TEST_H


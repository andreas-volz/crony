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
  CPPUNIT_TEST (myTest);
  CPPUNIT_TEST_SUITE_END ();

public:
  void setUp (void);
  void tearDown (void);

protected:
  void myTest (void);

private:
};

#endif // CRONTEST1_H


#ifndef CRON_TAB_TEST_H
#define CRON_TAB_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// STD
#include <string.h>

// local
#include "crony/Cron.h"

class CronTabTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE (CronTabTest);

  // 
  CPPUNIT_TEST (test1);

  CPPUNIT_TEST_SUITE_END ();

public:
  void setUp ();
  void tearDown ();

protected:
  void test1 ();

private:
  crony::DateTime mdtReference;
};

#endif // CRON_TAB_TEST_H

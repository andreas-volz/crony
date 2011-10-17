#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "CronTabTest.h"

using namespace std;
using namespace crony;

CPPUNIT_TEST_SUITE_REGISTRATION (CronTabTest);

void CronTabTest::setUp ()
{
  mdtReference.setYear (2010 - DateTime::YearShift);
  mdtReference.setMonth (DateTime::April);
  mdtReference.setDayOfMonth (13);
  mdtReference.setHours (11);
  mdtReference.setMinutes (10);
  mdtReference.setSeconds (0); // 0 is important as Cron assumes always 0!
  //cout << "mdtReference: " << endl << mdtReference << endl;
}

void CronTabTest::tearDown ()
{
  
}

void CronTabTest::test1 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setYear (mdtReference.getYear () + 1);
  
  cron1.setCurrentDateTime (mdtReference);

  std::list <Year> yearList;
  yearList.push_back (mdtReference.getYear () + DateTime::YearShift + 1);
  cron1.setYearList (yearList);

  cerr << endl; // only for log formating
  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

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
}

void CronTabTest::tearDown ()
{
  
}

void CronTabTest::test1 ()
{
  CronTab cronTab (false);
  Cron cron1;
  CronHit alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;

  cronTab.add (cron1);
  
  // check 1
  alarmExpect.setMinutes (mdtReference.getMinutes () + 1);
  
  cronTab.setCurrentDateTime (mdtReference);

  cerr << endl; // only for log formating
  alarmCalc = cronTab.calcNextTimer ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect.getTimestamp (), mdtReference.getTimestamp () + alarmCalc.timer);

  // check 2
  mdtReference.setMinutes (mdtReference.getMinutes () + 1);
  alarmExpect.setMinutes (mdtReference.getMinutes () + 1);
    
  cronTab.setCurrentDateTime (mdtReference);

  cerr << endl; // only for log formating
  alarmCalc = cronTab.calcNextTimer ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect.getTimestamp (), mdtReference.getTimestamp () + alarmCalc.timer);
}

void CronTabTest::test2 ()
{
  CronTab cronTab (false);
  Cron cron1;
  CronHit alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;

  std::list <Minute> minuteList;
  minuteList.push_back (mdtReference.getMinutes () + 2);
  cron1.setMinuteList (minuteList);
  
  cronTab.add (cron1);
  
  // check 1
  alarmExpect.setMinutes (mdtReference.getMinutes () + 2);

  cout << "mdtReference: " << mdtReference << endl;
  cout << "alarmExpect: " << alarmExpect << endl;
  
  cronTab.setCurrentDateTime (mdtReference);

  cerr << endl; // only for log formating
  alarmCalc = cronTab.calcNextTimer ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect.getTimestamp (), mdtReference.getTimestamp () + alarmCalc.timer);

  // check 2
  mdtReference.setMinutes (mdtReference.getMinutes () + 2);
  alarmExpect.setHours (mdtReference.getHours () + 1);

  cout << "mdtReference: " << mdtReference << endl;
  cout << "alarmExpect: " << alarmExpect << endl;
  
  cronTab.setCurrentDateTime (mdtReference);

  cerr << endl; // only for log formating
  alarmCalc = cronTab.calcNextTimer ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect.getTimestamp (), mdtReference.getTimestamp () + alarmCalc.timer);
}

#include "CronTest1.h"

CPPUNIT_TEST_SUITE_REGISTRATION (CronTest1);

void CronTest1::setUp (void)
{
  mdtReference.setYear (2010 - DateTime::YearShift);
  mdtReference.setMonth (DateTime::April);
  mdtReference.setDayOfMonth (13);
  mdtReference.setHours (11);
  mdtReference.setMinutes (0);
  mdtReference.setSeconds (0);
  mdtReference.calculate ();
  //cout << "mdtReference: " << endl << mdtReference << endl;
}

void CronTest1::tearDown (void)
{
  
}

void CronTest1::test1 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setYear (mdtReference.getYear () + 1);
  alarmExpect.calculate ();  

  cron1.setCurrentDateTime (mdtReference);

  std::list <Year> yearList;
  yearList.push_back (mdtReference.getYear () + 1 + DateTime::YearShift);
  cron1.setYearList (yearList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmCalc, alarmExpect);
}

void CronTest1::test2 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setMonth (mdtReference.getMonth () + 1);
  alarmExpect.calculate ();  

  cron1.setCurrentDateTime (mdtReference);

  std::list <Month> monthList;
  monthList.push_back (mdtReference.getMonth () + 1 + 1);
  cron1.setMonthList (monthList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmCalc, alarmExpect);
}


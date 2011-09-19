#include "CronTest1.h"

using namespace std;
using namespace crony;

CPPUNIT_TEST_SUITE_REGISTRATION (CronTest1);

void CronTest1::setUp (void)
{
  mdtReference.setYear (2010 - DateTime::YearShift);
  mdtReference.setMonth (DateTime::April);
  mdtReference.setDayOfMonth (13);
  mdtReference.setHours (11);
  mdtReference.setMinutes (10);
  mdtReference.setSeconds (0); // 0 is important as Cron assumes always 0!
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
  
  cron1.setCurrentDateTime (mdtReference);

  std::list <Year> yearList;
  yearList.push_back (mdtReference.getYear () + DateTime::YearShift + 1);
  cron1.setYearList (yearList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest1::test2 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setMonth (mdtReference.getMonth () + 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Month> monthList;
  monthList.push_back (mdtReference.getMonth () + 1 + 1); // +1 for time format...
  cron1.setMonthList (monthList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest1::test3 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setDayOfMonth (mdtReference.getDayOfMonth () + 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <DayOfMonth> dayOfMonthList;
  dayOfMonthList.push_back (mdtReference.getDayOfMonth () + 1);
  cron1.setDayOfMonthList (dayOfMonthList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest1::test4 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setDayOfMonth (alarmExpect.getDayOfMonth () + (alarmExpect.getDayOfWeek () - mdtReference.getDayOfWeek () + 1));

  cron1.setCurrentDateTime (mdtReference);

  std::list <DayOfWeek> dayOfWeekList;
  dayOfWeekList.push_back (mdtReference.getDayOfWeek () + 1);
  cron1.setDayOfWeekList (dayOfWeekList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest1::test5 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setHours (alarmExpect.getHours () + 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Hour> hourList;
  hourList.push_back (mdtReference.getHours () + 1);
  cron1.setHourList (hourList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest1::test6 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setMinutes (alarmExpect.getMinutes () + 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Minute> minuteList;
  minuteList.push_back (mdtReference.getMinutes () + 1);
  cron1.setMinuteList (minuteList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest1::test7 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setYear (mdtReference.getYear () + 1);
  alarmExpect.setMonth (mdtReference.getMonth () + 1);
  alarmExpect.setDayOfMonth (mdtReference.getDayOfMonth () + 1);
  alarmExpect.setHours (alarmExpect.getHours () + 1);
  alarmExpect.setMinutes (alarmExpect.getMinutes () + 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Year> yearList;
  yearList.push_back (mdtReference.getYear () + DateTime::YearShift + 1);
  cron1.setYearList (yearList);

  std::list <Month> monthList;
  monthList.push_back (mdtReference.getMonth () + 1 + 1); // +1 for time format...
  cron1.setMonthList (monthList);

  std::list <DayOfMonth> dayOfMonthList;
  dayOfMonthList.push_back (mdtReference.getDayOfMonth () + 1);
  cron1.setDayOfMonthList (dayOfMonthList);

  std::list <Hour> hourList;
  hourList.push_back (mdtReference.getHours () + 1);
  cron1.setHourList (hourList);
  
  std::list <Minute> minuteList;
  minuteList.push_back (mdtReference.getMinutes () + 1);
  cron1.setMinuteList (minuteList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest1::test8 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setMinutes (alarmExpect.getMinutes () + 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Minute> minuteList;
  minuteList.push_back (mdtReference.getMinutes ());
  minuteList.push_back (mdtReference.getMinutes () + 1);
  cron1.setMinuteList (minuteList);

  alarmCalc = cron1.calcNextHit ();
  
  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest1::test9 (void)
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setMinutes (alarmExpect.getMinutes () - 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Minute> minuteList;
  minuteList.push_back (mdtReference.getMinutes ());
  minuteList.push_back (mdtReference.getMinutes () + 1);
  cron1.setMinuteList (minuteList);

  try
  {
    alarmCalc = cron1.calcNextHit ();
  }
  catch (CronInPastException ex)
  {
    CPPUNIT_ASSERT (false);
  }
  
  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

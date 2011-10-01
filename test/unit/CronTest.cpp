#include "CronTest.h"

using namespace std;
using namespace crony;

CPPUNIT_TEST_SUITE_REGISTRATION (CronTest);

void CronTest::setUp ()
{
  mdtReference.setYear (2010 - DateTime::YearShift);
  mdtReference.setMonth (DateTime::April);
  mdtReference.setDayOfMonth (13);
  mdtReference.setHours (11);
  mdtReference.setMinutes (10);
  mdtReference.setSeconds (0); // 0 is important as Cron assumes always 0!
  //cout << "mdtReference: " << endl << mdtReference << endl;
}

void CronTest::tearDown ()
{
  
}

void CronTest::test1 ()
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

void CronTest::test2 ()
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

void CronTest::test3 ()
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

void CronTest::test4 ()
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

void CronTest::test5 ()
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

void CronTest::test6 ()
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

void CronTest::test7 ()
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

void CronTest::test8 ()
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

void CronTest::test9 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setMinutes (alarmExpect.getMinutes () - 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Minute> minuteList;
  minuteList.push_back (mdtReference.getMinutes () - 1);
  cron1.setMinuteList (minuteList);

  try
  {
    alarmCalc = cron1.calcNextHit ();
  }
  catch (CronInPastException ex)
  {
    // in this special unit test reaching the exception case is passed result...
    return;
  }

  // if exception is not hit there's an error in the algorithm, because time is in past
  CPPUNIT_ASSERT (false);
}

void CronTest::test10 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setHours (alarmExpect.getHours () - 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Hour> hourList;
  hourList.push_back (mdtReference.getHours () - 1);
  cron1.setHourList (hourList);

  try
  {
    alarmCalc = cron1.calcNextHit ();
  }
  catch (CronInPastException ex)
  {
    // in this special unit test reaching the exception case is passed result...
    return;
  }

  // if exception is not hit there's an error in the algorithm, because time is in past
  CPPUNIT_ASSERT (false);
}

void CronTest::test11 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setDayOfMonth (alarmExpect.getDayOfMonth () - 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <DayOfMonth> dayofmonthList;
  dayofmonthList.push_back (mdtReference.getDayOfMonth () - 1);
  cron1.setDayOfMonthList (dayofmonthList);

  try
  {
    alarmCalc = cron1.calcNextHit ();
  }
  catch (CronInPastException ex)
  {
    // in this special unit test reaching the exception case is passed result...
    return;
  }

  // if exception is not hit there's an error in the algorithm, because time is in past
  CPPUNIT_ASSERT (false);
}

void CronTest::test12 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setDayOfMonth (alarmExpect.getDayOfMonth () + 7 /* week */ - 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <DayOfWeek> dayofweekList;
  dayofweekList.push_back (mdtReference.getDayOfWeek () - 1);
  cron1.setDayOfWeekList (dayofweekList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest::test13 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setMonth (alarmExpect.getMonth () - 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Month> monthList;
  monthList.push_back (mdtReference.getMonth () - 1);
  cron1.setMonthList (monthList);

  try
  {
    alarmCalc = cron1.calcNextHit ();
  }
  catch (CronInPastException ex)
  {
    // in this special unit test reaching the exception case is passed result...
    return;
  }

  // if exception is not hit there's an error in the algorithm, because time is in past
  CPPUNIT_ASSERT (false);
}

void CronTest::test14 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  alarmExpect = mdtReference;
  alarmExpect.setYear (alarmExpect.getYear () - 1);

  cron1.setCurrentDateTime (mdtReference);

  std::list <Year> yearList;
  yearList.push_back (mdtReference.getYear () - 1);
  cron1.setYearList (yearList);

  try
  {
    alarmCalc = cron1.calcNextHit ();
  }
  catch (CronInPastException ex)
  {
    // in this special unit test reaching the exception case is passed result...
    return;
  }

  // if exception is not hit there's an error in the algorithm, because time is in past
  CPPUNIT_ASSERT (false);
}

void CronTest::test15 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  DateTime dtReference;
  dtReference.setYear (2011 - DateTime::YearShift);
  dtReference.setMonth (DateTime::September);
  dtReference.setDayOfMonth (30);
  dtReference.setHours (11);
  dtReference.setMinutes (10);
  dtReference.setSeconds (0); // 0 is important as Cron assumes always 0!

  alarmExpect = dtReference;
  alarmExpect.setDayOfMonth (alarmExpect.getDayOfMonth () + 7 /* week */ - 1);

  cron1.setCurrentDateTime (dtReference);

  std::list <DayOfWeek> dayofweekList;
  dayofweekList.push_back (dtReference.getDayOfWeek () - 1);
  cron1.setDayOfWeekList (dayofweekList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest::test16 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  DateTime dtReference;
  dtReference.setYear (2011 - DateTime::YearShift);
  dtReference.setMonth (DateTime::September);
  dtReference.setDayOfMonth (30);
  dtReference.setHours (11);
  dtReference.setMinutes (10);
  dtReference.setSeconds (0); // 0 is important as Cron assumes always 0!

  alarmExpect = dtReference;
  alarmExpect.setDayOfMonth (alarmExpect.getDayOfMonth () + 1);

  cron1.setCurrentDateTime (dtReference);

  std::list <DayOfWeek> dayofweekList;
  dayofweekList.push_back (dtReference.getDayOfWeek () + 1);
  cron1.setDayOfWeekList (dayofweekList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest::test17 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  DateTime dtReference;
  dtReference.setYear (2011 - DateTime::YearShift);
  dtReference.setMonth (DateTime::December);
  dtReference.setDayOfMonth (31);
  dtReference.setHours (11);
  dtReference.setMinutes (10);
  dtReference.setSeconds (0); // 0 is important as Cron assumes always 0!

  alarmExpect = dtReference;
  alarmExpect.setDayOfMonth (alarmExpect.getDayOfMonth () + 7 /* week */ - 1);

  cron1.setCurrentDateTime (dtReference);

  std::list <DayOfWeek> dayofweekList;
  dayofweekList.push_back (dtReference.getDayOfWeek () - 1);
  cron1.setDayOfWeekList (dayofweekList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

void CronTest::test18 ()
{
  Cron cron1;
  DateTime alarmCalc;
  DateTime alarmExpect;

  DateTime dtReference;
  dtReference.setYear (2011 - DateTime::YearShift);
  dtReference.setMonth (DateTime::December);
  dtReference.setDayOfMonth (31);
  dtReference.setHours (11);
  dtReference.setMinutes (10);
  dtReference.setSeconds (0); // 0 is important as Cron assumes always 0!

  alarmExpect = dtReference;
  alarmExpect.setDayOfMonth (alarmExpect.getDayOfMonth () + 1);

  cron1.setCurrentDateTime (dtReference);

  std::list <DayOfWeek> dayofweekList;
  dayofweekList.push_back (dtReference.getDayOfWeek () + 1);
  cron1.setDayOfWeekList (dayofweekList);

  alarmCalc = cron1.calcNextHit ();

  CPPUNIT_ASSERT_EQUAL (alarmExpect, alarmCalc);
}

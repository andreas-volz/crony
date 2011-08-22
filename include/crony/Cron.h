#ifndef CRON_H
#define CRON_H

// local
#include "DateTime.h"

// STD
#include <stdint.h>
#include <list>
#include <string>

typedef int Year;
typedef int DayOfWeek;
typedef int Month;
typedef int DayOfMonth;
typedef int Hour;
typedef int Minute;

/*! 
 * http://en.wikipedia.org/wiki/Cron
 */

class Cron
{
public:
  friend class CronTab;
  
  enum DayOfWeekEnum
  {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
  };

  enum MonthEnum
  {
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
  };
  
  Cron ();

  // TODO: all const reference parameters
  void setYearList (std::list <Year> yearList);

  void setDayOfWeekList (std::list <DayOfWeek> dayOfWeekList);
  
  void setMonthList (std::list <Month> monthList);

  void setDayOfMonthList (std::list <DayOfMonth> dayOfMonthList);

  void setHourList (std::list <Hour> hourList);

  void setMinuteList (std::list <Minute> minuteList);

  DateTime calcNextHit ();

  /*!
   * This function allows to set another current reference time.
   * Currently used to enable unit testing.
   */
  void setCurrentDateTime (DateTime current);
  
private:
  static const int MaxYearDiff = 2000;
  static const int MaxMonthDiff = 12;
  static const int MaxDayOfMonthDiff = 31;
  static const int MaxHourDiff = 24;
  static const int MaxMinuteDiff = 60;
  
  void checkYear (bool recheck = false);
  void checkMonth (bool recheck = false);
  void checkDayOfWeek (bool recheck = false);
  void checkDayOfMonth (bool recheck = false);
  void checkHour (bool recheck = false);
  void checkMinute (bool recheck = false);
  
  std::list <Year> mYearList;
  std::list <DayOfWeek> mDayOfWeekList;
  std::list <Month> mMonthList;
  std::list <DayOfMonth> mDayOfMonthList;
  std::list <Hour> mHourList;
  std::list <Minute> mMinuteList;

  DateTime mCurrent;
  DateTime mAlarm;
};

#endif // CRON_H

#ifndef CRON_H
#define CRON_H

// local
#include "DateTime.h"
#include "CronExceptions.h"

// STD
#include <stdint.h>
#include <list>
#include <string>

namespace crony {

typedef int Year;
typedef int DayOfWeek;
typedef int Month;
typedef int DayOfMonth;
typedef int Hour;
typedef int Minute;

/*! 
 * http://en.wikipedia.org/wiki/Cron
 
 *    *    *    *    *   * command to be executed
┬    ┬    ┬    ┬    ┬    \ year
│    │    │    │    │
│    │    │    │    │
│    │    │    │    └───── day of week (0 - 7) (Sunday=0 or 7)
│    │    │    └────────── month (1 - 12)
│    │    └─────────────── day of month (1 - 31)
│    └──────────────────── hour (0 - 23)
└───────────────────────── min (0 - 59)

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

  enum CronSteps
  {
    StepYear,
    StepMonth,
    StepDayOfMonthOrWeek,
    StepHour,
    StepMinute
  };
  
  Cron ();

  void setYearList (const std::list <Year> &yearList);

  void setDayOfWeekList (const std::list <DayOfWeek> &dayOfWeekList);
  
  void setMonthList (const std::list <Month> &monthList);

  void setDayOfMonthList (const std::list <DayOfMonth> &dayOfMonthList);

  void setHourList (const std::list <Hour> &hourList);

  void setMinuteList (const std::list <Minute> &minuteList);

  DateTime calcNextHit () const;

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
  
  bool checkYear (DateTime &mAlarm, bool recheck = false) const;
  bool checkMonth (DateTime &mAlarm, bool recheck = false) const;
  bool checkDayOfWeek (DateTime &mAlarm, bool recheck = false) const;
  bool checkDayOfMonth (DateTime &mAlarm, bool recheck = false) const;
  bool checkHour (DateTime &mAlarm, bool recheck = false) const;
  bool checkMinute (DateTime &mAlarm, bool recheck = false) const;

  bool isDayOfWeekMode () const;
  
  std::list <Year> mYearList;
  std::list <DayOfWeek> mDayOfWeekList;
  std::list <Month> mMonthList;
  std::list <DayOfMonth> mDayOfMonthList;
  std::list <Hour> mHourList;
  std::list <Minute> mMinuteList;

  DateTime mCurrent;
};

} // end namespace crony

#endif // CRON_H

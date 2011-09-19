// local
#include "crony/Cron.h"

// STD
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

Cron::Cron ()
{
}

void Cron::setYearList (const std::list <Year> &yearList)
{
  mYearList = yearList;
}

void Cron::setDayOfWeekList (const std::list <DayOfWeek> &dayOfWeekList)
{
  mDayOfWeekList = dayOfWeekList;
}

void Cron::setMonthList (const std::list <Month> &monthList)
{
  mMonthList = monthList;
}

void Cron::setDayOfMonthList (const std::list <DayOfMonth> &dayOfMonthList)
{
  mDayOfMonthList = dayOfMonthList;
}

void Cron::setHourList (const std::list <Hour> &hourList)
{
  mHourList = hourList;
}

void Cron::setMinuteList (const std::list <Minute> &minuteList)
{
  mMinuteList = minuteList;
}

DateTime Cron::calcNextHit () const
{
  DateTime alarmTime;
  alarmTime = mCurrent; // needed to realize other set time (e.g. for unit tests)
  
  // always hit at second at "0"
  alarmTime.setSeconds (0);

  checkYear (alarmTime);

  checkMonth (alarmTime);


  if ((mDayOfWeekList.size () == 0) && (mDayOfMonthList.size () == 0))
  {
    cerr << "match all '*' not allowed for both of dayofweek and dayofmonth" << endl;
    //assert (false);
    //return;
  }

  //checkDayOfWeek (alarmTime);

  checkDayOfMonth (alarmTime);

  // TODO: if dayofweek and dayofmonth are both * then abort
  // otherwise proceed with one of them

  checkHour (alarmTime);
  
  checkMinute (alarmTime);
  
  return alarmTime;
}

void Cron::checkYear (DateTime &alarmTime, bool recheck) const
{
  // hit all years (*)
  if (mYearList.size () == 0)
  {
    Year tmp = mCurrent.getYear ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setYear (tmp);
  }
  else
  {
    int yearDiff = MaxYearDiff;
    for (list <Year>::const_iterator y_it = mYearList.begin ();
         y_it != mYearList.end ();
         ++y_it)
    {
      Year year = *y_it;

      Year tmp = year - (mCurrent.getYear () + DateTime::YearShift); // convert to struct tm format

      // check for nearest value above
      if ((tmp >= 0) && (tmp <= yearDiff))
      {
        if (recheck)
        {
          if (year > (mCurrent.getYear () + DateTime::YearShift))
          {
            yearDiff = tmp;
          }
        }
        else
        {
          yearDiff = tmp;
        }
      }
    }

    if (yearDiff == MaxYearDiff)
    {
      cout << "not possible to hit year in past: no other possibility!" << endl;
      return;
    }
    else if (yearDiff > 0)
    {
      alarmTime.setYear (mCurrent.getYear () + yearDiff);
    }
  }
}

void Cron::checkMonth (DateTime &alarmTime, bool recheck) const
{  
  // hit all months (*)
  if (mMonthList.size () == 0)
  {
    Month tmp = mCurrent.getMonth ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setMonth (tmp);

    if (recheck)
    {
      checkYear (alarmTime);
    }
  }
  else
  {
    int monthDiff = MaxMonthDiff;
    for (list <Month>::const_iterator m_it = mMonthList.begin ();
         m_it != mMonthList.end ();
         ++m_it)
    {
      Month month = *m_it;
      --month; // convert to struct tm format

      Month tmp = month - mCurrent.getMonth ();

      // check for nearest value above
      if ((tmp >= 0) && (tmp <= monthDiff))
      {
        if (recheck)
        {
          if (month > mCurrent.getMonth ())
          {
            monthDiff = tmp;
          }
        }
        else
        {
          monthDiff = tmp;
        }
      }
    }

    if (monthDiff == MaxMonthDiff)
    {
      cout << "not possible to hit month in past: adding years" << endl;
      alarmTime.setMonth (*min_element (mMonthList.begin (), mMonthList.end ()));
      checkYear (alarmTime, true);
    }
    else if (monthDiff > 0)
    {
      alarmTime.setMonth (mCurrent.getMonth () + monthDiff);
    }
  }
}

void Cron::checkDayOfWeek (DateTime &alarmTime, bool recheck) const
{
 /* // first check for day of week and then...
  if (mDayOfWeekList.size () == 0)
  {
    alarmTime .setDayOfWeek (mCurrent.getDayOfWeek ());
  }
  else
  {
    int wday = mCurrent.getDayOfWeek ();
    int mday = mCurrent.getDayOfMonth ();
    
    // TODO: calc offset to monthday for next weekday hit...
  }*/
}

void Cron::checkDayOfMonth (DateTime &alarmTime, bool recheck) const
{
  // hit all months (*)
  if (mDayOfMonthList.size () == 0)
  {
    DayOfMonth tmp = mCurrent.getDayOfMonth ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setDayOfMonth (tmp);

    if (recheck)
    {
      checkMonth (alarmTime);
    }
  }
  else
  {
    int dayofmonthDiff = MaxDayOfMonthDiff;
    for (list <DayOfMonth>::const_iterator dom_it = mDayOfMonthList.begin ();
         dom_it != mDayOfMonthList.end ();
         ++dom_it)
    {
      DayOfMonth dayofmonth = *dom_it;

      DayOfMonth tmp = dayofmonth - mCurrent.getDayOfMonth ();

      // check for nearest value above
      if ((tmp >= 0) && (tmp <= dayofmonthDiff))
      {
        if (recheck)
        {
          if (dayofmonth > mCurrent.getDayOfMonth ())
          {
            dayofmonthDiff = tmp;
          }
        }
        else
        {
          dayofmonthDiff = tmp;
        }
      }
    }

    if (dayofmonthDiff == MaxDayOfMonthDiff)
    {
      cout << "not possible to hit day of month in past: adding month" << endl;
      alarmTime.setDayOfMonth (*min_element (mDayOfMonthList.begin (), mDayOfMonthList.end ()));
      checkMonth (alarmTime, true);
    }
    else if (dayofmonthDiff > 0)
    {
      alarmTime.setDayOfMonth (mCurrent.getDayOfMonth () + dayofmonthDiff);
    }
  }
}

void Cron::checkHour (DateTime &alarmTime, bool recheck) const
{
  // hit each hour (*)
  if (mHourList.size () == 0)
  {
    Hour tmp = mCurrent.getHours ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setHours (tmp);

    if (recheck)
    {
      // TODO: weekday or monthday??
      checkDayOfMonth (alarmTime);
    }
  }
  else
  {
    int hourDiff = MaxHourDiff;
    for (list <Hour>::const_iterator h_it = mHourList.begin ();
         h_it != mHourList.end ();
         ++h_it)
    {
      Hour hour = *h_it;

      Hour tmp = hour - mCurrent.getHours ();

      // check for nearest value above
      if ((tmp >= 0) && (tmp <= hourDiff))
      {
        if (recheck)
        {
          if (hour > mCurrent.getHours ())
          {
            hourDiff = tmp;
          }
        }
        else
        {
          hourDiff = tmp;
        }
      }
    }

    if (hourDiff == MaxHourDiff)
    {
      cout << "not possible to hit hour in past: adding days" << endl;
      alarmTime.setHours (*min_element (mHourList.begin (), mHourList.end ()));
      // TODO: weekday or monthday??
      checkDayOfMonth (alarmTime, true);
    }
    else if (hourDiff > 0)
    {
      alarmTime.setHours (mCurrent.getHours () + hourDiff);
    }
  }
}

void Cron::checkMinute (DateTime &alarmTime, bool recheck) const
{
  // hit each minute (*)
  if (mMinuteList.size () == 0)
  {
    Minute tmp = mCurrent.getMinutes ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setMinutes (tmp);

    if (recheck)
    {
      checkMinute (alarmTime);
    }
  }
  else
  {
    int minuteDiff = MaxMinuteDiff;
    for (list <Minute>::const_iterator m_it = mMinuteList.begin ();
         m_it != mMinuteList.end ();
         ++m_it)
    {
      Minute minute = *m_it;

      Minute tmp = minute - mCurrent.getMinutes ();

      // check for nearest value above
      if ((tmp >= 0) && (tmp <= minuteDiff))
      {
        if ((recheck) || (mCurrent.getHours () == alarmTime.getHours ()) )
        {
          if (minute > mCurrent.getMinutes ())
          {
            minuteDiff = tmp;
          }
        }
        else
        {
          minuteDiff = tmp;
        }
      }
    }

    if (minuteDiff == MaxMinuteDiff)
    {
      cout << "not possible to hit minute in past: adding hours" << endl;
      alarmTime.setMinutes (*min_element (mMinuteList.begin (), mMinuteList.end ()));
      checkHour (alarmTime, true);
    }
    else if (minuteDiff > 0)
    {
      alarmTime.setMinutes (mCurrent.getMinutes () + minuteDiff);
    }
  }
}

void Cron::setCurrentDateTime (DateTime current)
{
  mCurrent = current;
}

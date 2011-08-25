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

void Cron::setYearList (std::list <Year> yearList)
{
  mYearList = yearList;
}

void Cron::setDayOfWeekList (std::list <DayOfWeek> dayOfWeekList)
{
  mDayOfWeekList = dayOfWeekList;
}

void Cron::setMonthList (std::list <Month> monthList)
{
  mMonthList = monthList;
}

void Cron::setDayOfMonthList (std::list <DayOfMonth> dayOfMonthList)
{
  mDayOfMonthList = dayOfMonthList;
}

void Cron::setHourList (std::list <Hour> hourList)
{
  mHourList = hourList;
}

void Cron::setMinuteList (std::list <Minute> minuteList)
{
  mMinuteList = minuteList;
}

DateTime Cron::calcNextHit ()
{
  // always hit at second at "0"
  mAlarm.setSeconds (0);

  checkYear ();

  checkMonth ();


  if ((mDayOfWeekList.size () == 0) && (mDayOfMonthList.size () == 0))
  {
    cerr << "match all '*' not allowed for both of dayofweek and dayofmonth" << endl;
    //assert (false);
    //return;
  }

  //checkDayOfWeek ();

  checkDayOfMonth ();

  // TODO: if dayofweek and dayofmonth are both * then abort
  // otherwise proceed with one of them

  checkHour ();
  
  checkMinute ();
  
  return mAlarm;
}

void Cron::checkYear (bool recheck)
{
  // hit all years (*)
  if (mYearList.size () == 0)
  {
    Year tmp = mCurrent.getYear ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    mAlarm.setYear (tmp);
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
      mAlarm.setYear (mCurrent.getYear () + yearDiff);
    }
  }
}

void Cron::checkMonth (bool recheck)
{  
  // hit all months (*)
  if (mMonthList.size () == 0)
  {
    Month tmp = mCurrent.getMonth ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    mAlarm.setMonth (tmp);

    if (recheck)
    {
      checkYear ();
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
      mAlarm.setMonth (*min_element (mMonthList.begin (), mMonthList.end ()));
      checkYear (true);
    }
    else if (monthDiff > 0)
    {
      mAlarm.setMonth (mCurrent.getMonth () + monthDiff);
    }
  }
}

void Cron::checkDayOfWeek (bool recheck)
{
 /* // first check for day of week and then...
  if (mDayOfWeekList.size () == 0)
  {
    mAlarm .setDayOfWeek (mCurrent.getDayOfWeek ());
  }
  else
  {
    int wday = mCurrent.getDayOfWeek ();
    int mday = mCurrent.getDayOfMonth ();
    
    // TODO: calc offset to monthday for next weekday hit...
  }*/
}

void Cron::checkDayOfMonth (bool recheck)
{
  // hit all months (*)
  if (mDayOfMonthList.size () == 0)
  {
    DayOfMonth tmp = mCurrent.getDayOfMonth ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    mAlarm.setDayOfMonth (tmp);

    if (recheck)
    {
      checkMonth ();
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
      mAlarm.setDayOfMonth (*min_element (mDayOfMonthList.begin (), mDayOfMonthList.end ()));
      checkMonth (true);
    }
    else if (dayofmonthDiff > 0)
    {
      mAlarm.setDayOfMonth (mCurrent.getDayOfMonth () + dayofmonthDiff);
    }
  }
}

void Cron::checkHour (bool recheck)
{
  // hit each hour (*)
  if (mHourList.size () == 0)
  {
    Hour tmp = mCurrent.getHours ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    mAlarm.setHours (tmp);

    if (recheck)
    {
      // TODO: weekday or monthday??
      checkDayOfMonth ();
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
      mAlarm.setHours (*min_element (mHourList.begin (), mHourList.end ()));
      // TODO: weekday or monthday??
      checkDayOfMonth (true);
    }
    else if (hourDiff > 0)
    {
      mAlarm.setHours (mCurrent.getHours () + hourDiff);
    }
  }
}

void Cron::checkMinute (bool recheck)
{
  // hit each minute (*)
  if (mMinuteList.size () == 0)
  {
    Minute tmp = mCurrent.getMinutes ();
      
    if (recheck)
    {
      ++tmp;
    }
    
    mAlarm.setMinutes (tmp);

    if (recheck)
    {
      checkMinute ();
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
        if (recheck)
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
      cout << "not possible to hit minute in past: adding minutes" << endl;
      mAlarm.setMinutes (*min_element (mMinuteList.begin (), mMinuteList.end ()));
      checkHour (true);
    }
    else if (minuteDiff > 0)
    {
      mAlarm.setMinutes (mCurrent.getMinutes () + minuteDiff);
    }
  }
}

void Cron::setCurrentDateTime (DateTime current)
{
  mCurrent = current;
}

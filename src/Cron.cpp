#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// local
#include "crony/Cron.h"

// STD
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

namespace crony {

Cron::Cron () :
  mLogger ("crony.Cron")
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
  LOG4CXX_TRACE (mLogger, "calcNextHit");
  
  DateTime alarmTime;
  alarmTime = mCurrent; // needed to realize other set time (e.g. for unit tests)
  
  // always hit at second at "0"
  alarmTime.setSeconds (0);

  bool result = false;
  int step = StepYear;
  
  bool checkedYear = false;
  bool checkedMonth = false;
  bool checkedDayOfMonthOrWeek = false;
  bool checkedHour = false;
  bool checkedMinute = false;
  
  while (!result)
  {
    switch (step)
    {
      case StepYear:
      {
        result = checkYear (alarmTime, checkedYear);

        // set variables for next run
        checkedYear = true;
        checkedMonth = false;
        checkedDayOfMonthOrWeek = false;
        checkedHour = false;
        checkedMinute = false;

        if (!result) throw CronInPastException ();
      }
        
      case StepMonth:
      {
        result = checkMonth (alarmTime, checkedMonth);

        if (!result && checkedYear)
        {
          throw CronInPastException ();
        }
        
        // set variables for next run
        step = StepYear;
        checkedYear = true;
        checkedMonth = false;
        checkedDayOfMonthOrWeek = false;
        checkedHour = false;
        checkedMinute = false;

        if (!result) 
        {
          continue;
        }
      }
        
      case StepDayOfMonthOrWeek:
      {
        if (isDayOfWeekMode ())
        {
          result = checkDayOfWeek (alarmTime, checkedDayOfMonthOrWeek);
        }
        else
        {
          result = checkDayOfMonth (alarmTime, checkedDayOfMonthOrWeek);
        }

        if (!result && checkedYear && checkedMonth)
        {
          throw CronInPastException ();
        }
        
        // set variables for next run
        step = StepMonth;
        checkedYear = true;
        checkedMonth = true;
        checkedDayOfMonthOrWeek = false;
        checkedHour = false;
        checkedMinute = false;

        if (!result) 
        {
          continue;
        }
      }
        
      case StepHour:
      {
        result = checkHour (alarmTime, checkedHour);

        if (!result && checkedYear && checkedMonth && checkedDayOfMonthOrWeek)
        {
          throw CronInPastException ();
        }
        
        step = StepDayOfMonthOrWeek;
        checkedYear = true;
        checkedMonth = true;
        checkedDayOfMonthOrWeek = true;
        checkedHour = false;
        checkedMinute = false;
        
        if (!result) 
        {
          continue;
        }
      }
        
      case StepMinute:
      {
        result = checkMinute (alarmTime, checkedMinute);
        
        if (!result && checkedYear && checkedMonth && checkedDayOfMonthOrWeek && checkedHour)
        {
          throw CronInPastException ();
        }
        
        step = StepHour;
        checkedYear = true;
        checkedMonth = true;
        checkedDayOfMonthOrWeek = true;
        checkedHour = true;
        checkedMinute = false;
        
        if (!result) 
        {
          continue;
        }
      }
    }
  }

  return alarmTime;
}

bool Cron::checkYear (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkYear");
  
  bool result = true;
  
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
          if (year > (alarmTime.getYear () + DateTime::YearShift))
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
      result = false; // year in past
    }
    else if (yearDiff > 0)
    {
      alarmTime.setYear (mCurrent.getYear () + yearDiff);
    }
    else if (yearDiff < 0)
    {
      // should not happen; only to verify algorithm...
      assert (false);
    }
  }

  return result;
}

bool Cron::checkMonth (DateTime &alarmTime, bool recheck) const
{  
  LOG4CXX_TRACE (mLogger, "checkMonth");
  
  bool result = true;
  
  // hit all months (*)
  if (mMonthList.size () == 0)
  {
    Month tmp;

    if (mCurrent.getYear () != alarmTime.getYear ())
    {
      tmp = DateTime::January;
    }
    else
    {
      tmp = mCurrent.getMonth ();
    }
    
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setMonth (tmp);
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
      if (tmp <= monthDiff)
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
      LOG4CXX_INFO (mLogger, "not possible to hit month in past: adding years");
      alarmTime.setMonth (*min_element (mMonthList.begin (), mMonthList.end ()));
      result = false;
    }
    else
    {
      alarmTime.setMonth (mCurrent.getMonth () + monthDiff);
    }
  }

  return result;
}

// TODO
bool Cron::checkDayOfWeek (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkDayOfWeek");
  
  bool result = true;
  
  // hit all days (*)
  if (mDayOfWeekList.size () == 0)
  {
    DayOfMonth tmp_dayofmonth = mCurrent.getDayOfMonth ();
      
    if (recheck)
    {
      ++tmp_dayofmonth;
    }
    
    alarmTime.setDayOfMonth (tmp_dayofmonth);

    if (recheck)
    {
      result = false;
    }
  }
  else
  {
    int dayofmonthDiff = MaxDayOfMonthDiff;
    DayOfMonth dayofmonth = mCurrent.getDayOfMonth ();
    
    for (list <DayOfWeek>::const_iterator dow_it = mDayOfWeekList.begin ();
         dow_it != mDayOfWeekList.end ();
         ++dow_it)
    {
      DayOfWeek dayofweek = *dow_it;
      DayOfMonth tmp;
      
      if (dayofweek >= mCurrent.getDayOfWeek ())
      {
        tmp = mCurrent.getDayOfMonth () + (dayofweek - mCurrent.getDayOfWeek ());
      }
      else
      {
        tmp = mCurrent.getDayOfMonth () + (dayofweek - mCurrent.getDayOfWeek ()) + MaxDayOfWeekDiff;
      }

      // check for nearest value above
      if (tmp <= dayofmonthDiff)
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
      LOG4CXX_INFO (mLogger, "not possible to hit hour in past: adding month");
      alarmTime.setMonth (*min_element (mMonthList.begin (), mMonthList.end ()));

      result = false;
    }
    else
    {
      alarmTime.setDayOfMonth (dayofmonthDiff);
    }
  }

  return result;
}

bool Cron::checkDayOfMonth (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkDayOfMonth");
  
  bool result = true;
  
  // hit all days (*)
  if (mDayOfMonthList.size () == 0)
  {
    DayOfMonth tmp;

    if (mCurrent.getMonth () != alarmTime.getMonth ())
    {
      tmp = 1;
    }
    else
    {
      tmp = mCurrent.getDayOfMonth ();
    }
    
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setDayOfMonth (tmp);
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
      if (tmp <= dayofmonthDiff)
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
      LOG4CXX_INFO (mLogger, "not possible to hit day of month in past: adding month");
      alarmTime.setDayOfMonth (*min_element (mDayOfMonthList.begin (), mDayOfMonthList.end ()));
      result = false;
    }
    else
    {
      alarmTime.setDayOfMonth (mCurrent.getDayOfMonth () + dayofmonthDiff);
    }
  }

  return result;
}

bool Cron::checkHour (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkHour");
  
  bool result = true;
  
  // hit each hour (*)
  if (mHourList.size () == 0)
  {
    Hour tmp;
      
    if (mCurrent.getDayOfMonth () != alarmTime.getDayOfMonth ())
    {
      tmp = 0;
    }
    else
    {
      tmp = mCurrent.getHours ();
    }
    
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setHours (tmp);
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
      if (tmp <= hourDiff)
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
      LOG4CXX_INFO (mLogger, "not possible to hit hour in past: adding days");
      alarmTime.setHours (*min_element (mHourList.begin (), mHourList.end ()));

      result = false;
    }
    else
    {
      alarmTime.setHours (mCurrent.getHours () + hourDiff);
    }
  }

  return result;
}

bool Cron::checkMinute (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkMinute");
  
  bool result = true;
  
  // hit each minute (*)
  if (mMinuteList.size () == 0)
  {
    Minute tmp;
      
    if (mCurrent.getHours () != alarmTime.getHours ())
    {
      tmp = 0;
    }
    else
    {
      tmp = mCurrent.getMinutes () + 1; // alway hit next minute
    }
    
    if (recheck)
    {
      ++tmp;
    }
    
    alarmTime.setMinutes (tmp);
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
      if (tmp <= minuteDiff)
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

      // always hit next minute by adding one minute at current
      if (tmp == 0)
      {
        minuteDiff = 1;
      }
    }

    if (minuteDiff == MaxMinuteDiff)
    {
      LOG4CXX_INFO (mLogger, "not possible to hit minute in past: adding hours");
      alarmTime.setMinutes (*min_element (mMinuteList.begin (), mMinuteList.end ()));

      result = false;
    }
    else
    {
      alarmTime.setMinutes (mCurrent.getMinutes () + minuteDiff);
    }
  }

  return result;
}

void Cron::setCurrentDateTime (DateTime current)
{
  mCurrent = current;
}

bool Cron::isDayOfWeekMode () const
{
  if ((mDayOfMonthList.size () == 0) && (mDayOfWeekList.size () > 0))
  {
    return true;
  }

  return false;
}

} // end namespace crony

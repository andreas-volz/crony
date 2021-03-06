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
        LOG4CXX_TRACE (mLogger, "result=" << result);

        if (!result) throw CronInPastException ();
      }
        
      case StepMonth:
      {
        result = checkMonth (alarmTime, checkedMonth);
        LOG4CXX_TRACE (mLogger, "result=" << result);

        if (!result && checkedYear)
        {
          throw CronInPastException ();
        }
        
        // set variables for next run
        step = StepYear;
        checkedYear = true;

        if (!result) 
        {
          checkedMonth = true;
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
        LOG4CXX_TRACE (mLogger, "result=" << result);

        if (!result && checkedYear && checkedMonth)
        {
          throw CronInPastException ();
        }
        
        // set variables for next run
        step = StepMonth;
        checkedMonth = true;

        if (!result) 
        {
          checkedDayOfMonthOrWeek = true;
          continue;
        }
      }
        
      case StepHour:
      {
        result = checkHour (alarmTime, checkedHour);
        LOG4CXX_TRACE (mLogger, "result=" << result);

        if (!result && checkedYear && checkedMonth && checkedDayOfMonthOrWeek)
        {
          throw CronInPastException ();
        }
        
        step = StepDayOfMonthOrWeek;
        checkedDayOfMonthOrWeek = true;
        
        if (!result) 
        {
          checkedHour = true;
          continue;
        }
      }
        
      case StepMinute:
      {
        result = checkMinute (alarmTime, checkedMinute);
        LOG4CXX_TRACE (mLogger, "result=" << result);
        
        if (!result && checkedYear && checkedMonth && checkedDayOfMonthOrWeek && checkedHour)
        {
          throw CronInPastException ();
        }
        
        step = StepHour;
        checkedHour = true;
        
        if (!result) 
        {
          checkedMinute = true;
          continue;
        }
      }
    }
  }

  return alarmTime;
}

bool Cron::checkYear (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkYear, recheck=" << recheck);
  
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

      Year tmp = year - (mCurrent.getYear () + Cron::YearShift); // convert to struct tm format

      // check for nearest value above
      if ((tmp <= yearDiff) && (tmp > 0))
      {
        if (recheck)
        {
          if (year > (alarmTime.getYear () + Cron::YearShift))
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
  LOG4CXX_TRACE (mLogger, "checkMonth, recheck=" << recheck);

  bool isCurrent = mCurrent.getYear () == alarmTime.getYear ();

  bool result = true;
  
  // hit all months (*)
  if (mMonthList.size () == 0)
  {
    Month tmp;

    if (!isCurrent)
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
    LOG4CXX_DEBUG (mLogger, "setMonth/all = " << tmp);
  }
  else
  {
    if (!isCurrent)
    {
      Month tmp = *min_element (mMonthList.begin (), mMonthList.end ()) - Cron::MonthShift;
      alarmTime.setMonth (tmp);
      LOG4CXX_DEBUG (mLogger, "setMonth/minimum = " << tmp);
    }
    else
    {
      int monthDiff = MaxMonthDiff;
      for (list <Month>::const_iterator m_it = mMonthList.begin ();
           m_it != mMonthList.end ();
           ++m_it)
      {
        Month month = *m_it;
        month -= Cron::MonthShift; // convert to DateTime format

        Month tmp = month - mCurrent.getMonth ();

        // check for nearest value above
        if ((tmp <= monthDiff) && (tmp > 0))
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

      // if time on past handle as time not hit
      if (monthDiff < 0)
      {
        monthDiff = MaxMonthDiff;
      }

      if ((monthDiff == MaxMonthDiff) && (!recheck))
      {
        LOG4CXX_INFO (mLogger, "not possible to hit month in past: adding years");
        
        // only repeat last step only once -> if !recheck
        result = false;
      }
      else
      {
        Month tmp = mCurrent.getMonth () + monthDiff;
        alarmTime.setMonth (tmp);
        LOG4CXX_DEBUG (mLogger, "setMonth/specific = " << tmp);
      }
    }
  }

  return result;
}

bool Cron::checkDayOfWeek (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkDayOfWeek, recheck=" << recheck);

  bool isCurrent = mCurrent.getMonth () == alarmTime.getMonth ();
  
  bool result = true;
  
  // hit all days (*) - samo as hit all days of month!
  if (mDayOfWeekList.size () == 0)
  {
    DayOfMonth tmp;

    if (!isCurrent)
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
    LOG4CXX_DEBUG (mLogger, "setDayOfMonth/all = " << tmp);
  }
  else
  {
    if (!isCurrent)
    {
      DayOfMonth tmp = *min_element (mMonthList.begin (), mMonthList.end ());
      alarmTime.setMonth (tmp);
      LOG4CXX_DEBUG (mLogger, "setDayOfMonth/minimum = " << tmp);
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
        if ((tmp <= dayofmonthDiff) && (tmp > 0))
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

      // if time on past handle as time not hit
      if (dayofmonthDiff < 0)
      {
        dayofmonthDiff = MaxDayOfMonthDiff;
      }
      
      if ((dayofmonthDiff == MaxDayOfMonthDiff) && (!recheck))
      {
        LOG4CXX_INFO (mLogger, "not possible to hit hour in past: adding month");
        
        // only repeat last step only once
        result = false;
      }
      else
      {
        alarmTime.setDayOfMonth (dayofmonthDiff);
        LOG4CXX_DEBUG (mLogger, "setDayOfMonth/specific = " << dayofmonthDiff);
      }
    }
  }

  return result;
}

bool Cron::checkDayOfMonth (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkDayOfMonth, recheck=" << recheck);

  bool isCurrent = mCurrent.getMonth () == alarmTime.getMonth ();
  
  bool result = true;
  
  // hit all days (*)
  if (mDayOfMonthList.size () == 0)
  {
    DayOfMonth tmp;

    if (!isCurrent)
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
    LOG4CXX_DEBUG (mLogger, "setDayOfMonth/all = " << tmp);
  }
  else
  {
    if (!isCurrent)
    {
      DayOfMonth tmp = *min_element (mDayOfMonthList.begin (), mDayOfMonthList.end ());
      alarmTime.setDayOfMonth (tmp);
      LOG4CXX_DEBUG (mLogger, "setDayOfMonth/minimum = " << tmp);
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
        if ((tmp <= dayofmonthDiff) && (tmp > 0))
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

      // if time on past handle as time not hit
      if (dayofmonthDiff < 0)
      {
        dayofmonthDiff = MaxDayOfMonthDiff;
      }

      if ((dayofmonthDiff == MaxDayOfMonthDiff) && (!recheck))
      {
        LOG4CXX_INFO (mLogger, "not possible to hit day of month in past: adding month");

        // only repeat last step only once
        result = false;
      }
      else
      {
        DayOfMonth tmp = mCurrent.getDayOfMonth () + dayofmonthDiff;
        alarmTime.setDayOfMonth (tmp);
        LOG4CXX_DEBUG (mLogger, "setDayOfMonth/specific = " << tmp);
      }
    }
  }

  return result;
}

bool Cron::checkHour (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkHour, recheck=" << recheck);

  bool isCurrent = mCurrent.getDayOfMonth () == alarmTime.getDayOfMonth ();
  
  bool result = true;
  
  // hit each hour (*)
  if (mHourList.size () == 0)
  {
    Hour tmp;
      
    if (!isCurrent)
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
    LOG4CXX_DEBUG (mLogger, "checkHour, setHours/all = " << tmp);
  }
  else
  {
    if (!isCurrent)
    {
      Hour tmp = *min_element (mHourList.begin (), mHourList.end ());
      alarmTime.setHours (tmp);
      LOG4CXX_DEBUG (mLogger, "checkHour, setHours/minimum = " << tmp);
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
        if ((tmp <= hourDiff) && (tmp > 0))
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
   
      // if time on past handle as time not hit
      if (hourDiff < 0)
      {
        hourDiff = MaxHourDiff;
      }

      if ((hourDiff == MaxHourDiff) && (!recheck))
      {
        LOG4CXX_INFO (mLogger, "not possible to hit hour in past: adding days");

        // only repeat last step only once
        result = false;
      }
      else
      {
        Hour tmp = mCurrent.getHours () + hourDiff;
        alarmTime.setHours (tmp);
        LOG4CXX_DEBUG (mLogger, "checkHour, setHours/specific = " << tmp);
      }
    }
  }

  return result;
}

bool Cron::checkMinute (DateTime &alarmTime, bool recheck) const
{
  LOG4CXX_TRACE (mLogger, "checkMinute, recheck=" << recheck);

  bool isCurrent = mCurrent.getHours () == alarmTime.getHours ();
  
  bool result = true;
  
  // hit each minute (*)
  if (mMinuteList.size () == 0)
  {
    Minute tmp;
      
    if (!isCurrent)
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
    LOG4CXX_DEBUG (mLogger, "setMinute/all = " << tmp);
  }
  else
  {
    if (!isCurrent)
    {
      Minute tmp = *min_element (mMinuteList.begin (), mMinuteList.end ());
      alarmTime.setMinutes (tmp);
      LOG4CXX_DEBUG (mLogger, "setMinute/minumum = " << tmp);
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
        if ((tmp <= minuteDiff)  && (tmp > 0))
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

      // always hit next minute by adding one minute at current
      if (minuteDiff == 0)
      {
        minuteDiff = 1;
        result = false;
      }

      // if time on past handle as time not hit
      if (minuteDiff < 0)
      {
        minuteDiff = MaxMinuteDiff;
      }

      if ((minuteDiff == MaxMinuteDiff) && (!recheck))
      {
        LOG4CXX_INFO (mLogger, "not possible to hit minute in past: adding hours");

        // only repeat last step only once
        result = false;
      }
      else
      {
        Minute tmp = mCurrent.getMinutes () + minuteDiff;
        alarmTime.setMinutes (tmp);
        LOG4CXX_DEBUG (mLogger, "setMinute/specific = " << tmp);
      }
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

void Cron::setCommand (const std::string &command)
{
  mCommand = command;
}

std::string Cron::getCommand () const
{
  return mCommand;
}

} // end namespace crony

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "crony/DateTime.h"

// STD
#include <iostream>

using namespace std;

namespace crony {

DateTime::DateTime ()
{  
  // initialize each new DateTime to current system time
  current ();
}

DateTime::DateTime (time_t rawtime)
{
  localtime_r (&rawtime, &mTime);

  calculate ();
}

void DateTime::current ()
{
  time (&mRawtime);
  
  localtime_r (&mRawtime, &mTime);

  calculate ();
}

void DateTime::calculate ()
{
  mRawtime = mktime (&mTime);
}

int DateTime::getSeconds () const
{
  return mTime.tm_sec;
}

void DateTime::setSeconds (int sec)
{
  mTime.tm_sec = sec;
  calculate ();
}

int DateTime::getMinutes () const
{
  return mTime.tm_min;
}

void DateTime::setMinutes (int min)
{
  mTime.tm_min = min;
  calculate ();
}

int DateTime::getHours () const
{
  return mTime.tm_hour;
}

void DateTime::setHours (int hour)
{
  mTime.tm_hour = hour;
  calculate ();
}

int DateTime::getDayOfMonth () const
{
  return mTime.tm_mday;
}

void DateTime::setDayOfMonth (int mday)
{
  mTime.tm_mday = mday;
  calculate ();
}

int DateTime::getMonth () const
{
  return mTime.tm_mon;
}

void DateTime::setMonth (int mon)
{
  mTime.tm_mon = mon;
  calculate ();
}

int DateTime::getYear () const
{
  return mTime.tm_year;
}

void DateTime::setYear (int year)
{
  mTime.tm_year = year;
  calculate ();
}

bool DateTime::getDaylightSaving () const
{
  return mTime.tm_isdst;
}

void DateTime::setDayLightSaving (bool isdst)
{
  mTime.tm_isdst = isdst;
  calculate ();
}

//0-6
int DateTime::getDayOfWeek () const
{
  return mTime.tm_wday;
}

//0-365
int DateTime::getDayOfYear () const
{
  return mTime.tm_yday;
}

time_t DateTime::getTimestamp () const
{
  return mRawtime;
}

void DateTime::dump (std::ostringstream &outStream) const
{
  outStream  << "tm_sec: "   << mTime.tm_sec << endl
             << "tm_min: "   << mTime.tm_min << endl
             << "tm_hour: "  << mTime.tm_hour << endl
             << "tm_mday: "  << mTime.tm_mday << endl
             << "tm_mon: "   << mTime.tm_mon << endl
             << "tm_year: "  << mTime.tm_year << " == (" << 1900 + mTime.tm_year << ")" << endl
             << "tm_wday: "  << mTime.tm_wday << endl
             << "tm_yday: "  << mTime.tm_yday << endl
             << "tm_isdst: " << mTime.tm_isdst << endl
             << "rawtime: "  << mRawtime << endl;
}

double DateTime::operator - (const DateTime &dt) const
{
  return difftime (getTimestamp (), dt.getTimestamp ());
}

DateTime DateTime::operator + (const DateTime &dt) const
{
  double newTime;

  newTime = getTimestamp () + dt.getTimestamp ();
  
  return DateTime (newTime);
}

double DateTime::operator + (const time_t seconds) const
{
  return getTimestamp () + seconds;
}

bool operator == (const DateTime &dt1, const DateTime &dt2)
{
  return (dt1.getTimestamp () == dt2.getTimestamp ());
}

/// << operator for output
std::ostream &operator << (std::ostream &s, const DateTime &dt)
{
  std::ostringstream sLocal;
  dt.dump (sLocal);
    
  s << sLocal.str ();

  return s;
}

bool DateTime::operator < (const DateTime &dt) const
{
  return mRawtime < dt.mRawtime;
}

bool DateTime::operator > (const DateTime &dt) const
{
  return mRawtime > dt.mRawtime;
}

} // end namespace crony

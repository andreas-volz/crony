#include "crony/DateTime.h"

// STD
#include <iostream>

using namespace std;

DateTime::DateTime ()
{
  // initialize each new DateTime to current system time
  current ();
  calculate ();
}

void DateTime::current ()
{
  time (&mRawtime);
  
  localtime_r (&mRawtime, &mTime);
}

void DateTime::calculate ()
{
  mRawtime = mktime (&mTime);
  cout << mRawtime << endl;
}

int DateTime::getSeconds ()
{
  return mTime.tm_sec;
}

void DateTime::setSeconds (int sec)
{
  mTime.tm_sec = sec;
}

int DateTime::getMinutes ()
{
  return mTime.tm_min;
}

void DateTime::setMinutes (int min)
{
  mTime.tm_min = min;
}

int DateTime::getHours ()
{
  return mTime.tm_hour;
}

void DateTime::setHours (int hour)
{
  mTime.tm_hour = hour;
}

int DateTime::getDayOfMonth ()
{
  return mTime.tm_mday;
}

void DateTime::setDayOfMonth (int mday)
{
  mTime.tm_mday = mday;
}

int DateTime::getMonth ()
{
  return mTime.tm_mon;
}

void DateTime::setMonth (int mon)
{
  mTime.tm_mon = mon;
}

int DateTime::getYear ()
{
  return mTime.tm_year;
}

void DateTime::setYear (int year)
{
  mTime.tm_year = year;
}

bool DateTime::getDaylightSaving ()
{
  return mTime.tm_isdst;
}

void DateTime::setDayLightSaving (bool isdst)
{
  mTime.tm_isdst = isdst;
}

int DateTime::getDayOfWeek ()
{
  return mTime.tm_wday;
}

int DateTime::getDayOfYear ()
{
  return mTime.tm_yday;
}

time_t DateTime::getTimestamp ()
{
  return mRawtime;
}

double DateTime::operator - (const DateTime &dt)
{
  return difftime (mRawtime, dt.mRawtime);
}

// TODO: implement << operator
void DateTime::dump ()
{
  cout << "tm_sec: "   << mTime.tm_sec << endl
       << "tm_min: "   << mTime.tm_min << endl
       << "tm_hour: "  << mTime.tm_hour << endl
       << "tm_mday: "  << mTime.tm_mday << endl
       << "tm_mon: "   << mTime.tm_mon << endl
       << "tm_year: "  << mTime.tm_year << " == (" << 1900 + mTime.tm_year << ")" << endl
       << "tm_wday: "  << mTime.tm_wday << endl
       << "tm_yday: "  << mTime.tm_yday << endl
       << "tm_isdst: " << mTime.tm_isdst << endl
       << endl;
}
#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <ctime>

// TODO: think about recalculation flag...

class DateTime
{
public:
  enum WeekDay
  {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
  };

  DateTime ();
  
  void current ();

  void calculate ();

  int getSeconds ();
  void setSeconds (int sec);

  int getMinutes ();
  void setMinutes (int min);

  int getHours ();
  void setHours (int hour);

  int getDayOfMonth ();
  void setDayOfMonth (int mday);

  int getMonth ();
  void setMonth (int mon);

  int getYear ();
  void setYear (int year);
  
  bool getDaylightSaving ();
  void setDayLightSaving (bool isdst);

  // get only -> see 'enum WeekDay'
  int getDayOfWeek ();

  // get only
  int getDayOfYear ();

  time_t getTimestamp ();

  double operator - (const DateTime &dt);

  void dump ();

private:
  struct tm mTime;
  time_t mRawtime;
};

#endif // DATE_TIME_H

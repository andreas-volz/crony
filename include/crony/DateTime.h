#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <ctime>
#include <sstream>

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

  enum Month  
  {
    January = 0,
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

    // static variables
  static const int YearShift = 1900;
  
  // constructor
  DateTime ();

  // member functions
  void current ();

  void calculate ();

  //0-59
  int getSeconds ();
  void setSeconds (int sec);

  //0-59
  int getMinutes ();
  void setMinutes (int min);

  //0-23
  int getHours ();
  void setHours (int hour);

  //1-31
  int getDayOfMonth ();
  void setDayOfMonth (int mday);

  //0-11
  int getMonth ();
  void setMonth (int mon);

  // -1900 !!
  int getYear ();
  void setYear (int year);
  
  bool getDaylightSaving ();
  void setDayLightSaving (bool isdst);

  // get only -> see 'enum WeekDay'
  int getDayOfWeek ();

  // get only
  int getDayOfYear ();

  time_t getTimestamp () const;

  // operators
  
  double operator - (const DateTime &dt);

  friend std::ostream &operator << (std::ostream &s, const DateTime &dt);

  DateTime &operator = (const DateTime &dt);
  
private:
  void dump (std::ostringstream &outStream) const;
  
  struct tm mTime;
  time_t mRawtime;
};

// operators

std::ostream &operator << (std::ostream &s, const DateTime &dt);

bool operator == (const DateTime &dt, const DateTime &dt2);

#endif // DATE_TIME_H

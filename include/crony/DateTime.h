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

  //0-59
  int getSeconds () const;
  void setSeconds (int sec);

  //0-59
  int getMinutes () const;
  void setMinutes (int min);

  //0-23
  int getHours () const;
  void setHours (int hour);

  //1-31
  int getDayOfMonth () const;
  void setDayOfMonth (int mday);

  //0-11
  int getMonth () const;
  void setMonth (int mon);

  // -1900 !!
  int getYear () const;
  void setYear (int year);
  
  bool getDaylightSaving () const;
  void setDayLightSaving (bool isdst);

  // get only -> see 'enum WeekDay'
  int getDayOfWeek () const;

  // get only
  int getDayOfYear () const;

  time_t getTimestamp () const;

  // operators
  
  double operator - (const DateTime &dt) const;

  friend std::ostream &operator << (std::ostream &s, const DateTime &dt);
  
private:
  void calculate ();
  
  void dump (std::ostringstream &outStream) const;
  
  struct tm mTime;
  time_t mRawtime;
};

// operators

std::ostream &operator << (std::ostream &s, const DateTime &dt);

bool operator == (const DateTime &dt, const DateTime &dt2);

#endif // DATE_TIME_H

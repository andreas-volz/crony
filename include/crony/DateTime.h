#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <ctime>
#include <sstream>

namespace crony {

/*!
 * @see: man mktime
 */
class DateTime
{
public:
  enum WeekDay
  {
    Sunday = 0,
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
  
  // constructor
  DateTime ();

  // constructor
  DateTime (time_t rawtime);

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

  // 0-6
  int getDayOfWeek () const;

  // 0-365
  int getDayOfYear () const;

  time_t getTimestamp () const;

  // operators
  
  double operator - (const DateTime &dt) const; // TODO: fit API to + operator...

  DateTime operator + (const DateTime &dt) const;

  double operator + (const time_t seconds) const;

  bool operator < (const DateTime &dt) const;

  bool operator > (const DateTime &dt) const;

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

} // end namespace crony

#endif // DATE_TIME_H


// STD
#include <iostream>
#include <memory>
#include <ctime>

// EFL
//#include <ecorexx/Ecorexx.h>

// local
#include "crony/DateTime.h"
#include "crony/Cron.h"
#include "crony/CronTab.h"

using namespace std;

void dumpTime (tm *ptm);

/*bool timerEvent (Ecorexx::Timer &timer)
{
  cout << "timer hit at:" << endl;

  DateTime dt;
  dt.dump ();

  //sigc::slot <bool, Ecorexx::Timer&> timerSlot = sigc::ptr_fun (&timerEvent);
  //Ecorexx::Timer *timer2 = Ecorexx::Timer::factory (20, timerSlot);
  
  return false;
}*/

void dumpSeconds (double seconds)
{
  cout << "seconds: " << seconds << endl;
  cout << "minutes: " << (seconds /= 60) << endl;
  cout << "hours: " << (seconds /= 60) << endl;
  cout << "days: " << (seconds /= 24) << endl;
  cout << endl;
}

double secondsToHour (int hour)
{
  DateTime dt;
  DateTime alarm;
  double diff = 0;
  
  alarm.setHours (hour);
  alarm.setMinutes (0);
  alarm.setSeconds (0);

  diff = alarm - dt;

  if (diff < 0)
  {
    // increment alarm day because must be on next morning
    alarm.setDayOfMonth (alarm.getDayOfMonth () + 1);
    diff = alarm - dt;
  }

  cout << dt << endl;
  cout << alarm << endl;
  
  return diff;  
}

int main (int argc, const char **argv)
{
  /*auto_ptr <Ecorexx::Application> app (new Ecorexx::Application (argc, argv, "KidClock"));

  sigc::slot <bool, Ecorexx::Timer&> timerSlot = sigc::ptr_fun (&timerEvent);*/

  CronTab cronTab;

  Cron cronWeekday;

  static const bool dayofweek = false;
  if (dayofweek)
  {
    // MO-FR
    std::list <DayOfWeek> dayOfWeekList;
    //dayOfWeekList.push_back (Cron::Monday);
    dayOfWeekList.push_back (Cron::Tuesday);
    dayOfWeekList.push_back (Cron::Wednesday);
    dayOfWeekList.push_back (Cron::Thursday);
    //dayOfWeekList.push_back (Cron::Friday);
    cronWeekday.setDayOfWeekList (dayOfWeekList);
  }
  else
  {
    std::list <DayOfMonth> dayOfMonthList;
    dayOfMonthList.push_back (21);
    dayOfMonthList.push_back (7);
    dayOfMonthList.push_back (2);
    cronWeekday.setDayOfMonthList (dayOfMonthList);
  }

  std::list <Hour> hourList;
  hourList.push_back (2);
  cronWeekday.setHourList (hourList);

  std::list <Minute> minuteList;
  minuteList.push_back (5);
  minuteList.push_back (45);
  cronWeekday.setMinuteList (minuteList);

  std::list <Month> monthList;
  monthList.push_back (Cron::April);
  //monthList.push_back (Cron::December);
  cronWeekday.setMonthList (monthList);
  
  std::list <Year> yearList;
  yearList.push_back (2010);
  //yearList.push_back (2011);
  //yearList.push_back (2012);
  yearList.push_back (2013);
  //yearList.push_back (2012);
  cronWeekday.setYearList (yearList);

  cronTab.add (cronWeekday);

  // SA, SO
  /*Cron cronWeekend;
  std::list <DayOfWeek> dayOfWeekList2;
  dayOfWeekList2.push_back (Cron::Saturday);
  //dayOfWeekList2.push_back (Cron::Sunday);
  cronWeekend.setDayOfWeekList (dayOfWeekList2);

  std::list <Hour> hourList2;
  hourList2.push_back (8);
  cronWeekend.setHourList (hourList2);

  std::list <Minute> minuteList2;
  minuteList2.push_back (45);
  cronWeekend.setMinuteList (minuteList2);
  
  cronTab.add (cronWeekend);*/

  cronTab.calcNextTimer ();
  
  return 1; // TMP

  
  // http://www.cplusplus.com/reference/clibrary/ctime/tm/

  /*cout << "secondsToNextHour: " << endl;
  double diff = 10;//secondsToHour (7);
  dumpSeconds (diff);
  
  Ecorexx::Timer *timer = Ecorexx::Timer::factory (diff, timerSlot);

  app->exec();*/

  return 0;
}
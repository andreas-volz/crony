#ifndef CRON_TAB_H

// STD
#include <map>

// local
#include "Cron.h"
#include "DateTime.h"
#include "Logger.h"

namespace crony {

class CronHit
{
public:
  CronHit () : timer (0) {}
  
  time_t timer;
  std::string command;
  
private:
};
  
class CronTab
{
public:
  CronTab (bool autotimer = true);
  
  void add (const Cron &cron);

  CronHit calcNextTimer (); // const?

  /*!
   * This function allows to set another current reference time.
   * Currently used to enable unit testing.
   */
  void setCurrentDateTime (DateTime current);
  
private:
  std::map <DateTime, Cron> mTable;
  DateTime mCurrent;
  bool mAutotimer;
  Logger mLogger;
};

} // end namespace crony

#endif // CRON_TAB_H

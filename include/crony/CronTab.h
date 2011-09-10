#ifndef CRON_TAB_H

// STD
#include <map>

// local
#include "Cron.h"
#include "DateTime.h"

class CronTab
{
public:
  void add (const Cron &cron);

  void calcNextTimer ();
  
private:
  std::map <time_t, Cron> mTable;
};

#endif // CRON_TAB_H

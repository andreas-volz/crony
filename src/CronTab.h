#ifndef CRON_TAB_H

// STD
#include <list>

// local
#include "Cron.h"
#include "DateTime.h"

class CronTab
{
public:
  void add (const Cron &cron);

  void calcNextTimer ();
  
private:
  std::list <Cron> mTable;
};

#endif // CRON_TAB_H

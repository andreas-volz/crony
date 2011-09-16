#ifndef CRON_TAB_H

// STD
#include <map>

// SIGC
#include <sigc++/sigc++.h>

// local
#include "Cron.h"
#include "DateTime.h"

class CronTab
{
public:
  void add (const Cron &cron);

  time_t calcNextTimer ();

  sigc::signal<void> signalHit;
  
private:
  std::map <DateTime, Cron> mTable;
};

#endif // CRON_TAB_H

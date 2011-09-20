#ifndef CRON_TAB_H

// STD
#include <map>

// local
#include "Cron.h"
#include "DateTime.h"

namespace crony {

class CronTab
{
public:
  void add (const Cron &cron);

  time_t calcNextTimer ();
  
private:
  std::map <DateTime, Cron> mTable;
};

} // end namespace crony

#endif // CRON_TAB_H

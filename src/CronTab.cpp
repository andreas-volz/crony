#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// local
#include "crony/CronTab.h"

// STD
#include <iostream>

using namespace std;

namespace crony {

void CronTab::add (const Cron &cron)
{
  // TODO: potential problem if two cron with same time...
  mTable[cron.calcNextHit ()] = cron;
}

time_t CronTab::calcNextTimer ()
{
  for (map <DateTime, Cron>::iterator cr_it = mTable.begin ();
       cr_it != mTable.end ();
       ++cr_it)
  {
    DateTime current;
    DateTime keytime = cr_it->first;
    Cron cron = cr_it->second;

    cron.setCurrentDateTime (current);
    DateTime hittime = cron.calcNextHit ();
    cout << "Calc next hit: " << hittime << endl;
    if (hittime > current)
    {
      mTable.erase (cr_it);
      mTable[hittime] = cron;
      return hittime - current;
    }
  }

  return 0;
}

} // end namespace crony

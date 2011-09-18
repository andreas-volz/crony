// local
#include "crony/CronTab.h"

// STD
#include <iostream>

using namespace std;

void CronTab::add (const Cron &cron)
{
  // TODO: potential problem if two cron with same time...
  mTable[cron.calcNextHit ()] = cron;
}

time_t CronTab::calcNextTimer ()
{
  map <DateTime, Cron>::iterator cr_it = mTable.begin ();

  if (cr_it != mTable.end ())
  {
    DateTime current;
    DateTime hittime = cr_it->first;
    Cron cron = cr_it->second;
    
    cout << "Current: " << current << endl;
    cout << "Hit at: " << hittime << endl;

    if (hittime > current)
    {
      cout << "in future" << endl;
      return hittime - current;
    }
    
    // hit some callback at timestamp
    //signalHit.emit ();

    DateTime tmp = cron.calcNextHit ();
    cout << "tmp: " << tmp << endl;
    mTable.erase (cr_it);
    mTable[tmp] = cron;
  }

  return 0;
}

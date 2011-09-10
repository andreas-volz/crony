// local
#include "crony/CronTab.h"

// STD
#include <iostream>

using namespace std;

void CronTab::add (const Cron &cron)
{
  // TODO: potential problem if two cron with same time...
  mTable[cron.calcNextHit ().getTimestamp ()] = cron;
}

void CronTab::calcNextTimer ()
{
  map <time_t, Cron>::iterator cr_it = mTable.begin ();

  if (cr_it != mTable.end ())
  {
    time_t timestamp = cr_it->first;
    Cron &cron = cr_it->second;
    
    cout << "Hit at: " << DateTime (timestamp) << endl;

    // hit some callback at timestamp

    mTable[cron.calcNextHit ().getTimestamp ()] = cron;
    mTable.erase (cr_it);    
  }
  
}

// local
#include <CronTab.h>

// STD
#include <iostream>

using namespace std;

void CronTab::add (const Cron &cron)
{
  mTable.push_back (cron);  
}

void CronTab::calcNextTimer ()
{
  // TODO: calc only last run item
  for (std::list <Cron>::iterator c_it = mTable.begin ();
  c_it != mTable.end ();
  ++c_it)
  {
    Cron &cron = *c_it;
    
    cron.calcNextHit ();
  }
}

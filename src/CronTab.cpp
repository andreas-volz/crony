#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// local
#include "crony/CronTab.h"

// STD
#include <iostream>

using namespace std;

namespace crony {

CronTab::CronTab (bool autotimer) :
  mAutotimer (autotimer),
  mLogger ("crony.CronTab")
{
}

// TODO: think about handling Cron as pointer type...
void CronTab::add (const Cron &cron)
{
  // TODO: potential problem if two cron with same time...
  mTable[cron.calcNextHit ()] = cron;
}

time_t CronTab::calcNextTimer ()
{
  if (mAutotimer)
  {
    mCurrent.current ();
  }
  
  for (map <DateTime, Cron>::iterator cr_it = mTable.begin ();
       cr_it != mTable.end ();
       ++cr_it)
  {
    DateTime keytime = cr_it->first;
    Cron cron = cr_it->second;

    cron.setCurrentDateTime (mCurrent);
    DateTime hittime = cron.calcNextHit ();
    LOG4CXX_DEBUG (mLogger, "Calc next hit for: " << hittime);

    if (hittime > mCurrent)
    {
      mTable.erase (cr_it);
      mTable[hittime] = cron;
      return hittime - mCurrent;
    }
  }

  return 0;
}

void CronTab::setCurrentDateTime (DateTime current)
{
  mCurrent = current;
}

} // end namespace crony

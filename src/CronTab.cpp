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

CronHit CronTab::calcNextTimer ()
{
  CronHit returnCronHit;
  
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
    
    if (hittime > mCurrent)
    {
      LOG4CXX_DEBUG (mLogger, "Calc next Timer in: " << hittime - mCurrent << " sec");
      LOG4CXX_DEBUG (mLogger, "Calc next Timer for: " << hittime);

      returnCronHit.timer = hittime - mCurrent;
      returnCronHit.command = cron.getCommand ();
      
      mTable.erase (cr_it);
      mTable[hittime] = cron;
      return returnCronHit;
    }
  }

  /*map <DateTime, Cron>::iterator firstElement = mTable.begin ();

  if (firstElement != mTable.end ())
  {
    DateTime keytime = firstElement->first;
    Cron cron = firstElement->second;

      LOG4CXX_DEBUG (mLogger, "Calc next Timer in: " << keytime - mCurrent << " sec");
      LOG4CXX_DEBUG (mLogger, "Calc next Timer for: " << keytime);

    returnCronHit.timer = keytime - mCurrent;
    returnCronHit.command = cron.getCommand ();
  }*/

  // TODO: throw exception?
  return returnCronHit;
}

void CronTab::setCurrentDateTime (DateTime current)
{
  mCurrent = current;
}

} // end namespace crony

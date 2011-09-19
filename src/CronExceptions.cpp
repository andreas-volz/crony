#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* STD */
#include <string>

/* Project */
#include "crony/CronExceptions.h"
#include "stringUtil.h"

using namespace std;

namespace crony {

const char* CronInPastException::what () const throw ()
{
  static string s ("Cron date/time is in past - not possible to hit!");

  return static_cast <const char*> (s.c_str ());
}


} // end namespace crony

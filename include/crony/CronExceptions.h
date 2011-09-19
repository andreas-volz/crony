#ifndef CRON_EXCEPTIONS_H
#define CRON_EXCEPTIONS_H

/* STD */
#include <string>
#include <exception>

namespace crony {

class CronInPastException : public std::exception
{
public:
  CronInPastException () {}
  
  virtual ~CronInPastException () throw() {}

  const char* what () const throw ();

private:
};


} // end namespace crony

#endif // CRON_EXCEPTIONS_H

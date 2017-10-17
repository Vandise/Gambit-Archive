#ifndef __CHECKUNDEFINEDVARIABLE
#define __CHECKUNDEFINEDVARIABLE 1

#include "check/iEvent.hpp"

namespace Check
{
  class UndefinedVariable : public iEvent
  {

    public:
      using iEvent::iEvent;
      Check::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
#ifndef __CHECKUNDEFINEDMETHOD
#define __CHECKUNDEFINEDMETHOD 1

#include "check/iEvent.hpp"

namespace Check
{
  class UndefinedMethod : public iEvent
  {

    public:
      using iEvent::iEvent;
      Check::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
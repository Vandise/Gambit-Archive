#ifndef __CHECKINVALIDINTERFACEEVENT
#define __CHECKINVALIDINTERFACEEVENT 1

#include "check/iEvent.hpp"

namespace Check
{
  class InvalidInterfaceEvent : public iEvent
  {

    public:
      using iEvent::iEvent;
      Check::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
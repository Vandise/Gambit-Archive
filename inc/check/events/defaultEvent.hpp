#ifndef __CHECKDEFAULTEVENT
#define __CHECKDEFAULTEVENT 1

#include "check/iEvent.hpp"

namespace Check
{
  class DefaultEvent : public iEvent
  {

    public:
      using iEvent::iEvent;
      Check::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
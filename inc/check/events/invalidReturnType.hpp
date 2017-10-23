#ifndef __CHECKINVALIDRETURNTYPE
#define __CHECKINVALIDRETURNTYPE 1

#include "check/iEvent.hpp"

namespace Check
{
  class InvalidReturnType : public iEvent
  {

    public:
      using iEvent::iEvent;
      Check::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
#ifndef __CHECKUSELESSSTATEMENTEXCEPTION
#define __CHECKUSELESSSTATEMENTEXCEPTION 1

#include "check/iEvent.hpp"

namespace Check
{
  class UselessStatement : public iEvent
  {

    public:
      using iEvent::iEvent;
      Check::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
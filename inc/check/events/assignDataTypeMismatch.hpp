#ifndef __CHECKASSIGNDATATYPEMISMATCHEXCEPTION
#define __CHECKASSIGNDATATYPEMISMATCHEXCEPTION 1

#include "check/iEvent.hpp"

namespace Check
{
  class AssignDataTypeMismatch : public iEvent
  {

    public:
      using iEvent::iEvent;
      Check::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
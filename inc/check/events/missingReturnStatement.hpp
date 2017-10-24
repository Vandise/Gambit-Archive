#ifndef __CHECKMISSINGRETURNSTATEMENT
#define __CHECKMISSINGRETURNSTATEMENT 1

#include "check/iEvent.hpp"

namespace Check
{
  class MissingReturnStatement : public iEvent
  {

    public:
      using iEvent::iEvent;
      Check::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
#ifndef __UNEXPECTEDTOKENEXCEPTION
#define __UNEXPECTEDTOKENEXCEPTION 1

#include "check/iEvent.hpp"

namespace Check
{
  class UnexpectedToken : public iEvent
  {

    public:
      using iEvent::iEvent;
      UnexpectedToken::iEvent* with(std::vector<std::string> parameters);

  };
}

#endif
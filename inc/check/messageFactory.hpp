#ifndef __CHECKFACTORY
#define __CHECKFACTORY 1

#include "shared/check/iMessageFactory.hpp"
#include "check/events/defaultEvent.hpp"

namespace Check
{
  class MessageFactory : public iMessageFactory
  {

    public:
      MessageFactory(CaptureEvents e);
      ~MessageFactory();
      Check::iEvent* create();

  };
}

#endif
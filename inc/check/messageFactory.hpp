#ifndef __CHECKFACTORY
#define __CHECKFACTORY 1

#include "shared/exception/captureEvents.hpp"
#include "check/events/defaultEvent.hpp"

namespace Check
{
  class MessageFactory
  {
    private:
      Check::iEvent* E;

    public:
      MessageFactory(CaptureEvents e);
      ~MessageFactory();
      Check::iEvent* create();

  };
}

#endif
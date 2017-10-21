#ifndef __CHECKFACTORY
#define __CHECKFACTORY 1

#include "shared/check/iMessageFactory.hpp"
#include "check/events/defaultEvent.hpp"
#include "check/events/invalidInterfaceEvent.hpp"
#include "check/events/assignDataTypeMismatch.hpp"
#include "check/events/uselessStatement.hpp"
#include "check/events/unexpectedToken.hpp"
#include "check/events/undefinedVariable.hpp"
#include "check/events/undefinedMethod.hpp"

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
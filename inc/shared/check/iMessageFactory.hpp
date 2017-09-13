#ifndef __iCHECKFACTORY
#define __iCHECKFACTORY 1

#include "check/iEvent.hpp"
#include "shared/exception/captureEvents.hpp"

namespace Check
{

  class iMessageFactory
  {

    protected:
      Check::iEvent* E;

    public:
      virtual Check::iEvent* create() = 0;

  };

}

#endif
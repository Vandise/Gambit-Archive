#ifndef __RUNTIMEiMETHOD
#define __RUNTIMEiMETHOD 1

#include <vector>

namespace Runtime
{

  class iStandardClass;

  class iMethod
  {

    public:

      virtual Runtime::iStandardClass* call(Runtime::iStandardClass *receiver, std::vector<Runtime::iStandardClass*> arguments) = 0;

  };

}

#endif
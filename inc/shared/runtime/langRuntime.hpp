#ifndef __RUNTIMELANGRUNTIME
#define __RUNTIMELANGRUNTIME 1

#define REMOVED_FROM_RUNTIME(x) if (x != NULL) { delete(x); } x = NULL;

#include "runtime/objectspace/valueObject.hpp"

namespace Runtime
{

  class iObject;
  class iStandardClass;

  class LangRuntime
  {

    public:

      static ::Runtime::iStandardClass *klass;
      static ::Runtime::iStandardClass *objectClass;
      static ::Runtime::iStandardClass *mainObject;

      static void bootstrap();
      static void destroy();

  };

}

#endif
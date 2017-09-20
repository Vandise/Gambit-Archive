#ifndef __RUNTIMELANGRUNTIME
#define __RUNTIMELANGRUNTIME 1

namespace Runtime
{

  class iObject;
  class iStandardClass;

  class LangRuntime
  {

    public:

      static ::Runtime::iStandardClass *klass;
      static ::Runtime::iStandardClass *objectClass;
      static ::Runtime::iObject *mainObject;

      static void bootstrap();
      static void destroy();

  };

}

#endif
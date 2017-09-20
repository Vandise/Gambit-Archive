#ifndef __RUNTIMEiOBJECT
#define __RUNTIMEiOBJECT 1

#define DEFAULT_CLASS_NAME "Object"

#include <string>
#include "shared/runtime/iPrimitiveDataType.hpp"

namespace Runtime
{

  class iStandardClass;

  class iObject
  {

    protected:
      Runtime::iStandardClass *klass;

    public:

      iObject() = default;

      iObject(Runtime::iStandardClass *klass);
      iObject(std::string name);

      virtual ~iObject();
      virtual Runtime::iStandardClass* getStandardClass();
      virtual std::string getName();
      virtual void setStandardClass(Runtime::iStandardClass *klass);
      virtual Runtime::iPrimitiveDataType* getValue();

  };

}

#endif
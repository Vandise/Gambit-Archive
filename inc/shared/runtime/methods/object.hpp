#ifndef __RUNTIME_OBJECT_METHODS
#define __RUNTIME_OBJECT_METHODS 1

#include "shared/runtime/iStandardClass.hpp"
#include "shared/runtime/iMethod.hpp"

namespace Runtime
{

  class ObjectPutsStringMethod : public Runtime::iMethod
  {

    public:

      ObjectPutsStringMethod()
      {
        PARAMETER_TYPE("String")
      };

      virtual Runtime::iStandardClass* call(Runtime::iStandardClass *receiver, std::vector<Runtime::iStandardClass*> arguments)
      {
        Runtime::iStandardClass* str = arguments[0];
        Runtime::iPrimitiveDataType* cValue = str->getInstanceVariable("value")->getValue();

        std::cout << cValue->getString() << std::endl;
        delete(cValue);

        return receiver;
      };

  };

}
#endif
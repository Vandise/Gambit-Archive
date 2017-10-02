#ifndef __RUNTIMEVALUEOBJECT
#define __RUNTIMEVALUEOBJECT 1

#include <string>
#include "shared/runtime/iStandardClass.hpp"
#include "runtime/datatypes/primitive.hpp"

namespace Runtime
{

  class ValueObject : public Runtime::iStandardClass
  {

    private:
      PRIMITIVE_TYPE type;
      int intValue;
      std::string stringValue;

    public:

      using Runtime::iStandardClass::iStandardClass;

      ValueObject(std::string value);
      ValueObject(int value);
      virtual Runtime::iPrimitiveDataType* getValue();

  };

}

#endif
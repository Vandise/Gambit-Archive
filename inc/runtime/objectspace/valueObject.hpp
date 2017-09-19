#ifndef __RUNTIMEVALUEOBJECT
#define __RUNTIMEVALUEOBJECT 1

#include <string>
#include "shared/runtime/iObject.hpp"
#include "runtime/datatypes/primitive.hpp"

namespace Runtime
{

  class ValueObject : public Runtime::iObject
  {

    private:
      PRIMITIVE_TYPE type;
      int intValue;
      std::string stringValue;

    public:

      ValueObject(std::string value);
      ValueObject(int value);
      Runtime::iPrimitiveDataType* getValue();

  };

}

#endif
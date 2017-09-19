#ifndef __RUNTIMEPRIMITIVE
#define __RUNTIMEPRIMITIVE 1

#include <string>
#include "shared/runtime/iPrimitiveDataType.hpp"

namespace Runtime
{

  class Primitive : public Runtime::iPrimitiveDataType
  {

    public:

      using Runtime::iPrimitiveDataType::iPrimitiveDataType;

      Primitive(std::string value)
      {
        this->stringValue = value;
        this->type = STRING;
      };

      Primitive(int value)
      {
        this->intValue = value;
        this->type = INTEGER;
      };

  };

}

#endif
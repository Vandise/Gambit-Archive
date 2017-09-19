#ifndef __RUNTIMEiPRIMITIVE
#define __RUNTIMEiPRIMITIVE 1

#include <string>
#include "shared/runtime/primitiveTypes.hpp"

namespace Runtime
{

  class iPrimitiveDataType
  {

    protected:

      PRIMITIVE_TYPE type;
      int intValue;
      std::string stringValue;

    public:

      iPrimitiveDataType()
      {
        this->type = VOID;
      };

      virtual ~iPrimitiveDataType(){};

      virtual PRIMITIVE_TYPE getType()
      {
        return this->type;
      };

      virtual int getInteger()
      {
        return this->intValue;
      };

      virtual std::string getString()
      {
        return this->stringValue;
      };
  };

}

#endif
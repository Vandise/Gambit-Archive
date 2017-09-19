#ifndef __RUNTIMEiSTANDARDCLASS
#define __RUNTIMEiSTANDARDCLASS 1

#include <string>
#include "shared/runtime/iObject.hpp"

namespace Runtime
{

  class iObject;

  class iStandardClass : public Runtime::iObject
  {

    protected:

      std::string name;
      Runtime::iStandardClass *superClass;

    public:

      iStandardClass(std::string name, Runtime::iStandardClass *superClass)
      {
        this->name = name;
        this->superClass = superClass;
      };

      iStandardClass(std::string name)
      {
        this->name = name;
        // TODO: when the runtime is implemented, get and the "object class"
      };

      virtual ~iStandardClass()
      {
        if (this->superClass != nullptr)
        {
          delete(this->superClass);
        }
      };

      virtual std::string getName()
      {
        return this->name;
      };

  };

}

#endif
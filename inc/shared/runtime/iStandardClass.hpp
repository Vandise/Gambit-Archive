#ifndef __RUNTIMEiSTANDARDCLASS
#define __RUNTIMEiSTANDARDCLASS 1

#define IT_NOT_INITIAL_CLASSES it->first != "Object" && it->first != "Klass"

#include <string>
#include <iostream>
#include <map>
#include "shared/runtime/iObject.hpp"

namespace Runtime
{

  class iObject;

  class iStandardClass : public Runtime::iObject
  {

    protected:

      std::string name;
      std::map<std::string, Runtime::iStandardClass*> constants;
      Runtime::iStandardClass *superClass;

    public:

      using Runtime::iObject::iObject;

      iStandardClass(std::string name, Runtime::iStandardClass *superClass);

      iStandardClass(std::string name);

      virtual ~iStandardClass();

      virtual Runtime::iStandardClass* getSuperClass();

      virtual void setSuperClass(Runtime::iStandardClass *klass);

      virtual void setConstant(std::string name, Runtime::iStandardClass* klass);

      virtual bool hasConstant(std::string name);

      virtual Runtime::iStandardClass* getConstant(std::string name);

      virtual Runtime::iStandardClass* newInstance();

      virtual void newSubclass(std::string name);

      virtual std::string getName();

  };

}

#endif
#ifndef __RUNTIMEiOBJECT
#define __RUNTIMEiOBJECT 1

#define DEFAULT_CLASS_NAME "Object"

#include <string>
#include <map>
#include "shared/runtime/iMethod.hpp"
#include "shared/runtime/iPrimitiveDataType.hpp"

namespace Runtime
{

  class iStandardClass;

  class iObject
  {

    protected:
      Runtime::iStandardClass *klass;
      std::map<std::string, Runtime::iMethod*> methods;
      std::map<std::string, Runtime::iStandardClass*> instanceVariables;

    public:

      iObject() = default;

      iObject(Runtime::iStandardClass *klass);
      iObject(std::string name);

      virtual ~iObject();
      virtual Runtime::iStandardClass* getStandardClass();
      virtual std::string getName();
      virtual void setStandardClass(Runtime::iStandardClass *klass);
      virtual Runtime::iStandardClass* getInstanceVariable(std::string name);
      virtual bool hasInstanceVariable(std::string name);
      virtual void setInstanceVariable(std::string name, Runtime::iStandardClass* value);
      virtual Runtime::iPrimitiveDataType* getValue();
      virtual std::map<std::string, Runtime::iMethod*> getMethods();
      virtual std::map<std::string, Runtime::iStandardClass*> getInstanceVariables();
      virtual Runtime::iStandardClass* clone();

  };

}

#endif
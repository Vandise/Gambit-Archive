#ifndef __RUNTIMEiSTANDARDCLASS
#define __RUNTIMEiSTANDARDCLASS 1

#include <string>
#include <map>
#include "shared/runtime/iObject.hpp"
#include "shared/runtime/langRuntime.hpp"

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

      iStandardClass(std::string name, Runtime::iStandardClass *superClass)
      {
        this->name = name;
        this->superClass = superClass;
      };

      iStandardClass(std::string name)
      {
        this->name = name;
        this->klass = Runtime::LangRuntime::objectClass;
        this->superClass = Runtime::LangRuntime::objectClass;
      };

      virtual ~iStandardClass()
      {
        if (this->superClass != nullptr)
        {
          //delete(this->superClass);
        }
      };

      virtual Runtime::iStandardClass* getSuperClass()
      {
        return this->superClass;
      };

      virtual void setSuperClass(Runtime::iStandardClass *klass)
      {
        this->superClass = klass;
      };

      virtual void setConstant(std::string name, Runtime::iStandardClass* klass)
      {
        this->constants[name] = klass;
      };

      virtual bool hasConstant(std::string name)
      {
        if(this->constants.count(name) >= 1)
        {
          return true;
        }
        if(this->superClass)
        {
          return this->superClass->hasConstant(name);
        }
        return false;
      };

      virtual Runtime::iStandardClass* getConstant(std::string name)
      {
        if(this->constants.count(name) >= 1)
        {
          return this->constants[name];
        }
        if(this->superClass)
        {
          return this->superClass->getConstant(name);
        }
        // TODO: create exception
        return nullptr;
      };

      virtual std::string getName()
      {
        return this->name;
      };

  };

}

#endif
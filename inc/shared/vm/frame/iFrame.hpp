#ifndef __iVMFRAME
#define __iVMFRAME 1

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "shared/runtime/langRuntime.hpp"
#include "shared/runtime/iStandardClass.hpp"

namespace VM
{

  class iFrame
  {
    protected:
      std::string frameName;
      std::map<std::string, Runtime::iStandardClass*> locals;
      std::vector<Runtime::iStandardClass*> localStack;
      Runtime::iStandardClass* currentSelf;

    public:

      iFrame(std::string frameName)
      {
        this->frameName = frameName;
        this->currentSelf = Runtime::LangRuntime::mainObject;
      };

      virtual ~iFrame()
      {
        std::vector<Runtime::iStandardClass*>::iterator it;
        for(it = this->localStack.begin(); it != this->localStack.end(); it++)
        {
          delete(*it);
        }

        std::map<std::string, Runtime::iStandardClass*>::iterator iu;
        for(iu = this->locals.begin(); iu != this->locals.end(); iu++)
        {
          delete(iu->second);
        }

        this->localStack.clear();
      };

      virtual bool hasLocal(std::string name)
      {
        return (this->locals.count(name) > 0);
      };

      virtual void setLocal(std::string name, Runtime::iStandardClass* obj)
      {
        this->locals[name] = obj;
      };

      virtual Runtime::iStandardClass* getLocal(std::string local)
      {
        return this->locals[local];
      };

      virtual Runtime::iStandardClass* getCurrentSelf()
      {
        return this->currentSelf;
      };

      virtual std::string getFrameName()
      {
        return this->frameName;
      };

      virtual void pushStack(Runtime::iStandardClass* obj)
      {
        this->localStack.push_back(obj);
      };

      virtual Runtime::iStandardClass* popStack()
      {
        Runtime::iStandardClass* obj = this->localStack.back();
        this->localStack.pop_back();
        return obj;
      };

      virtual Runtime::iStandardClass* peekStack()
      {
        return this->localStack.back();
      };

  };

}

#endif
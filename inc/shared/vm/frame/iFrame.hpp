#ifndef __iVMFRAME
#define __iVMFRAME 1

#include <string>
#include <vector>
#include <iostream>

#include "shared/runtime/langRuntime.hpp"
#include "shared/runtime/iStandardClass.hpp"

namespace VM
{

  class iFrame
  {
    protected:
      std::string frameName;
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
        this->localStack.clear();
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
  };

}

#endif
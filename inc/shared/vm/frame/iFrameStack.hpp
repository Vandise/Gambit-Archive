#ifndef __iVMFRAMESTACK
#define __iVMFRAMESTACK 1

#include <stack>

#include "shared/vm/frame/iFrame.hpp"

namespace VM
{
  class iFrameStack
  {

    protected:

      std::stack<VM::iFrame*> frameStack;

    public:

      iFrameStack() = default;

      iFrameStack(VM::iFrame* f)
      {
        this->frameStack.push(f);
      };

      virtual ~iFrameStack()
      {
        for (int i = 0; i < this->frameStack.size(); i++)
        {
          VM::iFrame* f = this->frameStack.top();
          this->frameStack.pop();
          delete(f);
        }
      };

      virtual void pushFrame(VM::iFrame* frame)
      {
        this->frameStack.push(frame);
      };

      virtual bool popFrame()
      {
        if (!this->frameStack.empty())
        {
          this->frameStack.pop();
          return true;
        }
        return false;
      };

      virtual VM::iFrame* getCurrentFrame()
      {
        if (!this->frameStack.empty())
        {
          return this->frameStack.top();
        }
        return nullptr;
      };

      virtual int stackSize()
      {
        return this->frameStack.size();
      }

  };
}

#endif
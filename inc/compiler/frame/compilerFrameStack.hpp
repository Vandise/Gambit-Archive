#ifndef __COMPILERFRAMESTACK
#define __COMPILERFRAMESTACK 1

#include "shared/vm/frame/iFrameStack.hpp"
#include "compiler/frame/compilerFrame.hpp"

namespace Compiler
{

  class CompilerFrameStack : public VM::iFrameStack
  {
    using VM::iFrameStack::iFrameStack;
  };

}

#endif
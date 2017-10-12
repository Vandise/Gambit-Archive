#ifndef __ROOK_VM_PAWNEXECUTOR
#define __ROOK_VM_PAWNEXECUTOR 1

#define DEFAULT_FRAME "main"

#include <iostream>

#include "shared/runtime/langRuntime.hpp"
#include "shared/vm/frame/iFrameStack.hpp"

namespace RookAST
{
  class Tree;
}

namespace RookVM
{

  class PawnExecutor
  {

    protected:

      Runtime::iStandardClass* runtime;
      VM::iFrameStack *frameStack;
      RookAST::Tree *tree;

    public:

      PawnExecutor(RookAST::Tree *tree);

      virtual ~PawnExecutor();

      virtual void run();

      virtual Runtime::iStandardClass* getRuntime();
      virtual VM::iFrameStack* getFrameStack();

  };

}

#endif
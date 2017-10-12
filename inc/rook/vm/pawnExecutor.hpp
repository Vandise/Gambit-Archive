#ifndef __ROOK_VM_PAWNEXECUTOR
#define __ROOK_VM_PAWNEXECUTOR 1

#define DEFAULT_FRAME "main"

#include <iostream>

#include "shared/runtime/langRuntime.hpp"
#include "shared/vm/frame/iFrameStack.hpp"
#include "rook/vm/literalsTable.hpp"

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
      RookVM::LiteralsTable* literalsTable;

    public:

      PawnExecutor(RookAST::Tree *tree);

      virtual ~PawnExecutor();

      virtual void run();

      virtual Runtime::iStandardClass* getRuntime();
      virtual VM::iFrameStack* getFrameStack();
      virtual RookVM::LiteralsTable* getLiteralsTable();

  };

}

#endif
#ifndef __ROOK_VM_PAWNEXECUTOR
#define __ROOK_VM_PAWNEXECUTOR 1

#define DEFAULT_FRAME "main"

#include <iostream>

#include "rook/ast/tree.hpp"
#include "shared/runtime/langRuntime.hpp"
#include "shared/vm/frame/iFrameStack.hpp"

namespace RookVM
{

  class PawnExecutor
  {

    protected:

      Runtime::iStandardClass* runtime;
      VM::iFrameStack *frameStack;
      RookAST::Tree *tree;

    public:

      PawnExecutor(RookAST::Tree *tree)
      {
        this->runtime = Runtime::LangRuntime::objectClass;
        this->frameStack = new VM::iFrameStack();
        this->frameStack->pushFrame( (new VM::iFrame(DEFAULT_FRAME)) );
        this->tree = tree;
      };

      virtual ~PawnExecutor()
      {
        delete(this->tree);
        delete(this->frameStack);
      }

      virtual void run()
      {
        this->tree->compile();
      };

      virtual Runtime::iStandardClass* getRuntime()
      {
        return this->runtime;
      };

  };

}

#endif
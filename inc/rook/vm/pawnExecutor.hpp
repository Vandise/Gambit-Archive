#ifndef __ROOK_VM_PAWNEXECUTOR
#define __ROOK_VM_PAWNEXECUTOR 1

#define DEFAULT_FRAME "main"

#include <map>
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

      int currentNode = 0;
      bool terminated = false;
      Runtime::iStandardClass* runtime;
      VM::iFrameStack *frameStack;
      RookAST::Tree *tree;
      RookVM::LiteralsTable* literalsTable;
      std::map<std::string, int> labels;

    public:

      PawnExecutor(RookAST::Tree *tree);

      virtual ~PawnExecutor();

      virtual void run();

      virtual Runtime::iStandardClass* getRuntime();
      virtual VM::iFrameStack* getFrameStack();
      virtual RookVM::LiteralsTable* getLiteralsTable();
      virtual void incrementNodePointer();
      virtual void setNodePointer(int value);
      virtual int getNodePointer();
      virtual bool hasLabel(std::string label);
      virtual void addLabel(std::string label);
      virtual void jumpToLabel(std::string label);
      virtual int labelSize();
      virtual std::map<std::string, int> getLabels();
      virtual void terminate();
      virtual bool isTerminated();

  };

}

#endif
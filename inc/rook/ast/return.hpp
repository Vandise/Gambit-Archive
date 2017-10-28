#ifndef __ROOK_RETURNNODE
#define __ROOK_RETURNNODE 1

#include "rook/ast/node.hpp"

namespace RookAST
{

  class ReturnNode : public RookAST::Node
  {

    protected:
      int popStack;

    public:

      ReturnNode(int popStack);
      ~ReturnNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
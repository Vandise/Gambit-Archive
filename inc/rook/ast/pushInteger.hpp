#ifndef __ROOK_PUSHINTEGERNODE
#define __ROOK_PUSHINTEGERNODE 1

#include "rook/ast/node.hpp"

namespace RookAST
{

  class PushIntegerNode : public RookAST::Node
  {

    protected:
      int value;

    public:

      PushIntegerNode(int value);
      ~PushIntegerNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
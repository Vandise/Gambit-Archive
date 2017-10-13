#ifndef __ROOK_PUSHSTRINGNODE
#define __ROOK_PUSHSTRINGNODE 1

#include "rook/ast/node.hpp"

namespace RookAST
{

  class PushStringNode : public RookAST::Node
  {

    protected:
      int literalOffset;

    public:

      PushStringNode(int literalOffset);
      ~PushStringNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
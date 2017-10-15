#ifndef __ROOK_PUSHSELFNODE
#define __ROOK_PUSHSELFNODE 1

#include "rook/ast/node.hpp"

namespace RookAST
{

  class PushSelfNode : public RookAST::Node
  {

    public:

      PushSelfNode();
      ~PushSelfNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
#ifndef __ROOK_GETLOCALNODE
#define __ROOK_GETLOCALNODE 1

#include <string>
#include "rook/ast/node.hpp"

namespace RookAST
{

  class GetLocalNode : public RookAST::Node
  {

    protected:
      int identifierOffset;

    public:

      GetLocalNode(int identifierOffset);
      ~GetLocalNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
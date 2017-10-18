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
      bool isClone;

    public:

      GetLocalNode(int identifierOffset, bool isClone);
      ~GetLocalNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
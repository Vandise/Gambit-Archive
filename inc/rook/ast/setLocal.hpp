#ifndef __ROOK_SETLOCALNODE
#define __ROOK_SETLOCALNODE 1

#include <string>
#include "rook/ast/node.hpp"

namespace RookAST
{

  class SetLocalNode : public RookAST::Node
  {

    protected:
      std::string constant;
      int identifierOffset;

    public:

      SetLocalNode(std::string constant, int identifierOffset);
      ~SetLocalNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
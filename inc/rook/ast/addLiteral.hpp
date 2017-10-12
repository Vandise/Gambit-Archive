#ifndef __ROOK_ADDLITERALNODE
#define __ROOK_ADDLITERALNODE 1

#include "rook/ast/node.hpp"

namespace RookAST
{

  class AddLiteralNode : public RookAST::Node
  {

    protected:
      std::string literal;

    public:

      AddLiteralNode(std::string literal);
      ~AddLiteralNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
#ifndef __ROOK_AST_NODE
#define __ROOK_AST_NODE 1

#include <iostream>
#include "shared/ast/sourceTrace.hpp"

namespace RookAST
{

  class Node
  {

    public:
      virtual ~Node() {};
      virtual void compile() = 0;

  };

}

#endif
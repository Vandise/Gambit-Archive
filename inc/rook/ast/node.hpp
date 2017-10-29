#ifndef __ROOK_AST_NODE
#define __ROOK_AST_NODE 1

#include <iostream>
#include "shared/runtime/iStandardClass.hpp"
#include "runtime/objectspace/valueObject.hpp"
#include "rook/vm/pawnExecutor.hpp"
#include "shared/dev/board.hpp"

namespace RookAST
{

  class Node
  {

    public:
      virtual ~Node() {};
      virtual void compile(RookVM::PawnExecutor* e) = 0;
      virtual std::string getType()
      {
        return "Node";
      };

  };

}

#endif
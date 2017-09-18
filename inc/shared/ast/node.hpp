#ifndef __AST_NODE
#define __AST_NODE 1

#include <iostream>
#include "shared/compiler/iCodeGenerator.hpp"

namespace AST
{

  class Node
  {
    public:
      virtual ~Node(){};
      virtual void compile(Compiler::iCodeGenerator *cg) = 0;

  };

}

#endif
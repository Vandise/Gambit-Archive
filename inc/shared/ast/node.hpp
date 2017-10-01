#ifndef __AST_NODE
#define __AST_NODE 1

#include <iostream>
#include "shared/ast/sourceTrace.hpp"
#include "shared/compiler/iCodeGenerator.hpp"

namespace AST
{

  class Node
  {
    protected:
      AST::SourceTrace* trace;

    public:
      virtual ~Node()
      {
        delete(this->trace);
      };
      virtual void compile(Compiler::iCodeGenerator *cg) = 0;
      virtual AST::SourceTrace* getTrace()
      {
        return this->trace;
      };

  };

}

#endif
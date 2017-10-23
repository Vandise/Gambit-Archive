#ifndef __GAMBIT_RETURNNODE
#define __GAMBIT_RETURNNODE 1

#include "shared/ast/node.hpp"

namespace Gambit
{

  class ReturnNode : public AST::Node
  {

    private:
      AST::Node* expression;

    public:

      ReturnNode(AST::Node* expression, AST::SourceTrace* trace);
      ~ReturnNode();
      void compile(Compiler::iCodeGenerator *cg);

  };

}

#endif
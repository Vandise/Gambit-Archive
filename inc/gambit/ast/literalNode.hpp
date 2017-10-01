#ifndef __GAMBIT_LITERALNODE
#define __GAMBIT_LITERALNODE 1

#include "shared/ast/node.hpp"

namespace Gambit
{

  class LiteralNode : public AST::Node
  {

    private:
      int intValue;

    public:

      LiteralNode(int value, AST::SourceTrace* trace);
      ~LiteralNode();
      void compile(Compiler::iCodeGenerator *cg);

  };

}

#endif
#ifndef __GAMBIT_LITERALNODE
#define __GAMBIT_LITERALNODE 1

#include "shared/ast/node.hpp"

namespace Gambit
{

  class LiteralNode : public AST::Node
  {

    private:
      int type = 0;
      int intValue;
      std::string stringValue;

    public:

      LiteralNode(int value, AST::SourceTrace* trace);
      LiteralNode(std::string stringValue, AST::SourceTrace* trace);
      ~LiteralNode();
      void compile(Compiler::iCodeGenerator *cg);

  };

}

#endif
#ifndef __GAMBIT_LOCALDEFINITIONNODE
#define __GAMBIT_LOCALDEFINITIONNODE 1

#include "shared/ast/node.hpp"

namespace Gambit
{

  class LocalDefinitionNode : public AST::Node
  {

    private:
      std::string identifier;
      std::string className;
      AST::Node* valueNode = nullptr;

    public:

      LocalDefinitionNode(std::string className, std::string identifier, AST::Node* expression, AST::SourceTrace* trace);
      ~LocalDefinitionNode();
      void compile(Compiler::iCodeGenerator *cg);

  };

}

#endif

#ifndef __GAMBIT_METHOD_DEFINITION_NODE
#define __GAMBIT_METHOD_DEFINITION_NODE 1

#include "shared/ast/node.hpp"
#include "gambit/ast/parameters.hpp"

namespace Gambit
{

  class MethodDefinitionNode : public AST::Node
  {

    private:
      Gambit::Parameters* params;
      std::string identifier;
      std::string returnType;
      AST::Node* body;
      AST::SourceTrace* trace;

    public:

      MethodDefinitionNode(std::string identifier, Gambit::Parameters* params, std::string returnType, AST::Node* body, AST::SourceTrace* trace);
      ~MethodDefinitionNode();
      void compile(Compiler::iCodeGenerator *cg);

  };

}

#endif
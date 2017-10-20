#include "gambit/ast/methodDefinitionNode.hpp"

Gambit::MethodDefinitionNode::MethodDefinitionNode(std::string identifier, Gambit::Parameters* params, std::string returnType, AST::Node* body, AST::SourceTrace* trace)
{
  this->identifier = identifier;
  this->params = params;
  this->returnType = returnType;
  this->body = body;
  this->trace = trace;
}

Gambit::MethodDefinitionNode::~MethodDefinitionNode()
{
  delete(this->body);
  delete(this->params);
  delete(this->trace);
}

void
Gambit::MethodDefinitionNode::compile(Compiler::iCodeGenerator *cg)
{
  std::cout << "Compiling method definition" << std::endl;
}
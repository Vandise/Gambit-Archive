#include "gambit/ast/localDefinitionNode.hpp"
#include <iostream>

Gambit::LocalDefinitionNode::LocalDefinitionNode(std::string className, std::string identifier, AST::Node* expression)
{
  this->identifier = identifier;
  this->className = className;
  this->valueNode = expression;
}

Gambit::LocalDefinitionNode::~LocalDefinitionNode()
{
  if (this->valueNode != nullptr)
  {
    delete(this->valueNode);
  }
}

void
Gambit::LocalDefinitionNode::compile(Compiler::iCodeGenerator *cg)
{
  cg->setState(CS_LOCAL_DEFINITION);

  bool isNull = true;

  if (this->valueNode != nullptr)
  {
    this->valueNode->compile(cg);
    isNull = false;
  }

  cg->emit()->setLocal(this->className, this->identifier, isNull);

  cg->popState();
}
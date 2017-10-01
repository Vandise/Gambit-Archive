#include "gambit/ast/literalNode.hpp"


Gambit::LiteralNode::LiteralNode(int value, AST::SourceTrace* trace)
{
  this->intValue = value;
  this->trace = trace;
}

Gambit::LiteralNode::~LiteralNode()
{

}

void
Gambit::LiteralNode::compile(Compiler::iCodeGenerator *cg)
{
  cg->emit()->withTrace(this->trace)->pushInteger(this->intValue);
}
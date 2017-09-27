#include "gambit/ast/literalNode.hpp"


Gambit::LiteralNode::LiteralNode(int value)
{
  this->intValue = value;
}

Gambit::LiteralNode::~LiteralNode()
{

}

void
Gambit::LiteralNode::compile(Compiler::iCodeGenerator *cg)
{
  cg->emit()->pushInteger(this->intValue);
}
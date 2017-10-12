#include "gambit/ast/literalNode.hpp"


Gambit::LiteralNode::LiteralNode(int value, AST::SourceTrace* trace)
{
  this->type = 1;
  this->intValue = value;
  this->trace = trace;
}

Gambit::LiteralNode::LiteralNode(std::string stringValue, AST::SourceTrace* trace)
{
  this->type = 2;
  this->stringValue = stringValue;
  this->trace = trace;
}

Gambit::LiteralNode::~LiteralNode()
{

}

void
Gambit::LiteralNode::compile(Compiler::iCodeGenerator *cg)
{
  if ( this->type == 1 )
  {
    cg->emit()->withTrace(this->trace)->pushInteger(this->intValue);
  }

  if ( this->type == 2 )
  {
    cg->emit()->withTrace(this->trace)->pushString(this->stringValue);
  }
}
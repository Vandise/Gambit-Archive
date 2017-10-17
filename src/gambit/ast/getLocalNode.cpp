#include "gambit/ast/getLocalNode.hpp"

Gambit::GetLocalNode::GetLocalNode(std::string identifier, AST::SourceTrace* trace)
{
  this->identifier = identifier;
  this->trace = trace;
}

Gambit::GetLocalNode::~GetLocalNode()
{

}

void
Gambit::GetLocalNode::compile(Compiler::iCodeGenerator *cg)
{
  cg->emit()->withTrace(this->trace)->getLocal(this->identifier);
}
#include "gambit/ast/callNode.hpp"


Gambit::CallNode::CallNode(std::string identifier, Gambit::Arguments *args, AST::SourceTrace* trace)
{
  this->identifier = identifier;
  this->arguments = args;
  this->trace = trace;
}

Gambit::CallNode::~CallNode()
{
  delete(this->arguments);
}

void
Gambit::CallNode::compile(Compiler::iCodeGenerator *cg)
{
  std::cout << "Compiling call to: " << this->identifier << std::endl;
  /*
  if ( this->type == 1 )
  {
    cg->emit()->withTrace(this->trace)->pushInteger(this->intValue);
  }
  */

}
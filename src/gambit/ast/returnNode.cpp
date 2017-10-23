#include "gambit/ast/returnNode.hpp"


Gambit::ReturnNode::ReturnNode(AST::Node* expression, AST::SourceTrace* trace)
{
  this->expression = expression;
  this->trace = trace;
}

Gambit::ReturnNode::~ReturnNode()
{
  if ( this->expression != nullptr ) { delete(this->expression); }
}

void
Gambit::ReturnNode::compile(Compiler::iCodeGenerator *cg)
{
  cg->setState(CS_RETURN);
  //
  // Something was returned and pushed to the stack
  //  Otherwise treat everything as VOID
  //
  bool returnNode = false;

  if ( this->expression != nullptr )
  {
    returnNode = true;
  }

  cg->emit()->withTrace(this->trace)->putReturn(returnNode, this->expression);
  cg->popState();
}
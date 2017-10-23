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
  /*
  //
  // Something was returned and pushed to the stack
  //  Otherwise treat everything as VOID
  //
  if ( this->expression != nullptr )
  {
    cg->triggerFlag(RETURN_FLAG);
  }

  this->expression->compile(cg);

  cg->emit()->withTrace(this->trace)->putReturn(
    cg->getFlag(RETURN_FLAG)
  );
  */
}
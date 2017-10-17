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
  std::vector<AST::Node *> args = this->arguments->getArgs();

  cg->setState(CS_ARGUMENTS);

  std::vector<AST::Node *>::iterator it;
  for (it = args.begin(); it != args.end(); it++)
  {
    (*it)->compile(cg);

    // generate method signature 
    this->identifier.append("_").append(
      cg->getFrameStack()->getCurrentFrame()->peekStack()->getName()
    );

  }

  cg->popState();

  cg->setState(CS_CALL);

  std::string klassName = cg->getFrameStack()->getCurrentFrame()->getCurrentSelf()->getName();

  cg->emit()->withTrace(this->trace)->pushSelf();
  cg->emit()->withTrace(this->trace)->call(klassName.append("_").append(this->identifier), args.size());

  cg->popState();
}
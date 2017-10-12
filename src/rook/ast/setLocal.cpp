#include "rook/ast/setLocal.hpp"

RookAST::SetLocalNode::SetLocalNode(std::string constant, int identifierOffset)
{
  this->constant = constant;
  this->identifierOffset = identifierOffset;
}

RookAST::SetLocalNode::~SetLocalNode()
{

}

void
RookAST::SetLocalNode::compile(RookVM::PawnExecutor* e)
{

  std::cout << "Compiling SET_LOCAL: " << this->constant << " " << this->identifierOffset << std::endl;
  if ( e->getFrameStack()->getCurrentFrame()->peekStack()->getName() == this->constant )
  {
    Runtime::iStandardClass* klass = e->getFrameStack()->getCurrentFrame()->popStack();
    e->getFrameStack()->getCurrentFrame()->setLocal(
      e->getLiteralsTable()->getLiteral(this->identifierOffset),
      klass
    );
    klass = nullptr;
  }

  // if this got past the compiler, then I clearly did something wrong
  //    throw an exception

}
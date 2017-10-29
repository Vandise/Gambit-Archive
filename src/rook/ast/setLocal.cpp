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

  if ( e->getFrameStack()->getCurrentFrame()->peekStack()->getName() == this->constant )
  {
    Runtime::iStandardClass* klass = e->getFrameStack()->getCurrentFrame()->popStack();

    Dev::Board::sendMessage(std::string("POP_STACK|").append(klass->getName()));

    e->getFrameStack()->getCurrentFrame()->setLocal(
      e->getLiteralsTable()->getLiteral(this->identifierOffset),
      klass
    );

    Dev::Board::sendMessage(std::string("SET_LOCAL|").append(
      e->getLiteralsTable()->getLiteral(this->identifierOffset)
    ).append(",").append(klass->getName()));

    klass = nullptr;
  }

  e->incrementNodePointer();

  // if this got past the compiler, then I clearly did something wrong
  //    throw an exception

}
#include "rook/ast/getLocal.hpp"

RookAST::GetLocalNode::GetLocalNode(int identifierOffset, bool isClone)
{
  this->identifierOffset = identifierOffset;
  this->isClone = isClone;
}

RookAST::GetLocalNode::~GetLocalNode()
{

}

void
RookAST::GetLocalNode::compile(RookVM::PawnExecutor* e)
{
  std::string local = e->getLiteralsTable()->getLiteral(this->identifierOffset);
  Dev::Board::sendMessage(std::string("LOG|Get local,").append(local).append(",").append(std::to_string(this->identifierOffset)));

  Runtime::iStandardClass* l = e->getFrameStack()->getCurrentFrame()->getLocal(local);
  if (this->isClone)
  {
    l = l->clone();
  }

  Dev::Board::sendMessage(std::string("PUSH_STACK|").append(local).append(",").append(std::to_string(this->identifierOffset)).append(",").append(
    std::to_string(this->isClone)
  ));
  e->getFrameStack()->getCurrentFrame()->pushStack(l);
    l = nullptr;

  e->incrementNodePointer();

}
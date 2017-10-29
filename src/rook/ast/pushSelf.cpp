#include "rook/ast/pushSelf.hpp"

RookAST::PushSelfNode::PushSelfNode()
{

}

RookAST::PushSelfNode::~PushSelfNode()
{
  
}

void
RookAST::PushSelfNode::compile(RookVM::PawnExecutor* e)
{
  Dev::Board::sendMessage(std::string("PUSH_STACK|").append(
    e->getFrameStack()->getCurrentFrame()->getCurrentSelf()->getName()
  ));
  e->getFrameStack()->getCurrentFrame()->pushStack(
    e->getFrameStack()->getCurrentFrame()->getCurrentSelf()
  );
  e->incrementNodePointer();
}
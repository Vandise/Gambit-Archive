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
    Dev::Board::formatClassMsg(e->getFrameStack()->getCurrentFrame()->getCurrentSelf())
  ));
  e->getFrameStack()->getCurrentFrame()->pushStack(
    e->getFrameStack()->getCurrentFrame()->getCurrentSelf()
  );
  e->incrementNodePointer();
}
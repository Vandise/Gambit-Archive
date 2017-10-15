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
  std::cout << "PUSH_SELF" << std::endl;
  e->getFrameStack()->getCurrentFrame()->pushStack(
    e->getFrameStack()->getCurrentFrame()->getCurrentSelf()
  );
  e->incrementNodePointer();
}
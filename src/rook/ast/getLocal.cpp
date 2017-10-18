#include "rook/ast/getLocal.hpp"

RookAST::GetLocalNode::GetLocalNode(int identifierOffset)
{
  this->identifierOffset = identifierOffset;
}

RookAST::GetLocalNode::~GetLocalNode()
{

}

void
RookAST::GetLocalNode::compile(RookVM::PawnExecutor* e)
{
  // TODO:
  //  Handle cloning for parameters
  //
  std::cout << "Compiling GET_LOCAL: " << this->identifierOffset << std::endl;
  std::string local = e->getLiteralsTable()->getLiteral(this->identifierOffset);

  e->getFrameStack()->getCurrentFrame()->pushStack(
    e->getFrameStack()->getCurrentFrame()->getLocal(local)->clone()
  );

  e->incrementNodePointer();

}
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
  // TODO:
  //  Handle cloning for parameters
  //
  std::cout << "Compiling GET_LOCAL: " << this->identifierOffset << std::endl;
  std::string local = e->getLiteralsTable()->getLiteral(this->identifierOffset);

  Runtime::iStandardClass* l = e->getFrameStack()->getCurrentFrame()->getLocal(local);
  if (this->isClone)
  {
    l = l->clone();
  }

  e->getFrameStack()->getCurrentFrame()->pushStack(l);
    l = nullptr;

  e->incrementNodePointer();

}
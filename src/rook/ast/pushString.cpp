#include "rook/ast/pushString.hpp"

RookAST::PushStringNode::PushStringNode(int literalOffset)
{
  this->literalOffset = literalOffset;
}

RookAST::PushStringNode::~PushStringNode()
{
  
}

void
RookAST::PushStringNode::compile(RookVM::PawnExecutor* e)
{
  Runtime::iStandardClass* str = e->getRuntime()->getConstant("String")->newInstance();
  str->setInstanceVariable("value", (new Runtime::ValueObject(
    e->getLiteralsTable()->getLiteral(this->literalOffset) ))
  );

  Dev::Board::sendMessage(std::string("PUSH_STACK|").append(
    e->getLiteralsTable()->getLiteral(this->literalOffset)
  ));

  e->getFrameStack()->getCurrentFrame()->pushStack(str);
    str = nullptr;

  e->incrementNodePointer();

}
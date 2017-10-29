#include "rook/ast/pushInteger.hpp"

RookAST::PushIntegerNode::PushIntegerNode(int value)
{
  this->value = value;
}

RookAST::PushIntegerNode::~PushIntegerNode()
{
  
}

void
RookAST::PushIntegerNode::compile(RookVM::PawnExecutor* e)
{
  Runtime::iStandardClass* integer = e->getRuntime()->getConstant("Integer")->newInstance();
  integer->setInstanceVariable("value", (new Runtime::ValueObject(value)) );

  Dev::Board::sendMessage(std::string("PUSH_STACK|").append(std::to_string(this->value)));
  e->getFrameStack()->getCurrentFrame()->pushStack(integer);
    integer = nullptr;

  e->incrementNodePointer();

}
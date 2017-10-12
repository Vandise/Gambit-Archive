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
  std::cout << "Compiling PUSH_INTEGER: " << this->value << std::endl;

  Runtime::iStandardClass* integer = e->getRuntime()->getConstant("Integer")->newInstance();
  integer->setInstanceVariable("value", (new Runtime::ValueObject(value)) );

  e->getFrameStack()->getCurrentFrame()->pushStack(integer);
    integer = nullptr;

}
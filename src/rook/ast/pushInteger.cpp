#include "rook/ast/pushInteger.hpp"

RookAST::PushIntegerNode::PushIntegerNode(int value)
{
  this->value = value;
}

RookAST::PushIntegerNode::~PushIntegerNode()
{
  
}

void
RookAST::PushIntegerNode::compile()
{
  std::cout << "Compiling PUSH_INTEGER: " << this->value << std::endl;
}
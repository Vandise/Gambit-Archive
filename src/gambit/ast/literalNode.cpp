#include "gambit/ast/literalNode.hpp"


Gambit::LiteralNode::LiteralNode(int value)
{
  this->intValue = value;
}

Gambit::LiteralNode::~LiteralNode()
{

}

void
Gambit::LiteralNode::compile()
{
  std::cout << "Compiling Type: Integer" << " with value: " << intValue << " Addr: " <<  this << std::endl;
}
#include "rook/ast/setLocal.hpp"

RookAST::SetLocalNode::SetLocalNode(std::string constant, int identifierOffset)
{
  this->constant = constant;
  this->identifierOffset = identifierOffset;
}

RookAST::SetLocalNode::~SetLocalNode()
{

}

void
RookAST::SetLocalNode::compile()
{
  std::cout << "Compiling SET_LOCAL: " << this->constant << " " << this->identifierOffset << std::endl;
}
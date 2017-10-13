#include "rook/ast/label.hpp"

RookAST::LabelNode::LabelNode(std::string label)
{
  this->label = label;
}

RookAST::LabelNode::~LabelNode()
{
  
}

void
RookAST::LabelNode::compile(RookVM::PawnExecutor* e)
{
  e->addLabel(this->label);
  e->incrementNodePointer();
}
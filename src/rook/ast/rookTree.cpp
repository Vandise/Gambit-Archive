#include "rook/ast/rookTree.hpp"

RookAST::RookTree::RookTree(std::vector<RookAST::Node*> nodes)
{
  this->nodes = nodes;
}

RookAST::RookTree::~RookTree()
{

}

void
RookAST::RookTree::pushNodes(std::vector<RookAST::Node*> nodes)
{
  this->nodes = nodes;
}

void
RookAST::RookTree::pushBranch(RookAST::Tree *tree)
{
  this->nodes.push_back(tree);
}

void
RookAST::RookTree::pushNode(RookAST::Node *node)
{
  this->nodes.push_back(node);
}

int
RookAST::RookTree::treeSize()
{
  return 0;
}

void
RookAST::RookTree::compile()
{

}
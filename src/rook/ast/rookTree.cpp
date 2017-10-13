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
RookAST::RookTree::compile(RookVM::PawnExecutor* e)
{
  int treeSize = this->nodes.size();
  e->setNodePointer(0);


  //
  //  The Executor process loop for each instruction.
  //    - tree
  //    -- main branch
  //    --- node
  //    --- labelnode1
  //    --- node
  //    --- go to labelnode1 if condition 
  //
  while(e->getNodePointer() < treeSize)
  {
    RookAST::Node* n = this->nodes[e->getNodePointer()];
    if (n != nullptr ) { n->compile(e); } else { e->incrementNodePointer(); }
  }
}
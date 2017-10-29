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

std::string
RookAST::RookTree::getType()
{
  return "RookTree";
}

void
RookAST::RookTree::compile(RookVM::PawnExecutor* e)
{
  int treeSize = this->nodes.size();
  e->setNodePointer(0);

  //
  // Preprocess labels
  //
  Dev::Board::sendMessage(std::string("LOG|Preprocessing Labels"));
  for (auto &n : nodes)
  {
    if ( n->getType() == "LabelNode" )
    {
      if (n != nullptr) n->compile(e);
    }
    else
    {
      e->incrementNodePointer();
    }
  }

  e->setNodePointer(0);
  Dev::Board::sendMessage(std::string("LOG|Executing instructions"));
  //
  //  The Executor process loop for each instruction.
  //    - tree
  //    -- main branch
  //    --- node
  //    --- labelnode1
  //    --- node
  //    --- go to labelnode1 if condition 
  //
  while(e->getNodePointer() < treeSize && !e->isTerminated() )
  {
    RookAST::Node* n = this->nodes[e->getNodePointer()];
    if (n != nullptr ) { n->compile(e); } else { e->incrementNodePointer(); }
  }
}
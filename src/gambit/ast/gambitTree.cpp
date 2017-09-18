#include "gambit/ast/gambitTree.hpp"

Gambit::Tree::Tree(std::vector<AST::Node*> nodes)
{
  this->nodes = nodes;
}

Gambit::Tree::~Tree()
{

}

void
Gambit::Tree::pushNodes(std::vector<AST::Node*> nodes)
{
  this->nodes = nodes;
}

void
Gambit::Tree::pushBranch(AST::Tree *tree)
{
  this->nodes.push_back(tree);
}

void
Gambit::Tree::pushNode(AST::Node *node)
{
  this->nodes.push_back(node);
}

int
Gambit::Tree::treeSize()
{
  return 0;
}

void
Gambit::Tree::compile(Compiler::iCodeGenerator *cg)
{
  for (auto &n : nodes)
  {
    n->compile(cg);
  }
  cg->setState(CS_DEFAULT);
}
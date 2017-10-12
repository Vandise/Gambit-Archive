#ifndef __AST_TREE
#define __AST_TREE 1

#include <iostream>
#include <vector>

#include "rook/ast/node.hpp"

namespace RookAST
{

  class Tree : public Node
  {

    public:
      virtual ~Tree(){
        for (auto &n : this->nodes)
        {
          if (n != nullptr) delete(n);
        }
      };
      virtual void pushNodes(std::vector<RookAST::Node*> nodes) = 0;
      virtual void pushBranch(RookAST::Tree *tree) = 0;
      virtual void pushNode(RookAST::Node *node) = 0;
      virtual int treeSize() = 0;
      virtual void compile() = 0;

    protected:
      std::vector<RookAST::Node*> nodes;

  };

}

#endif
#ifndef __ROOK_TREE_HPP__
#define __ROOK_TREE_HPP__ 1

#include "rook/ast/tree.hpp"

namespace RookAST
{

  class RookTree : public RookAST::Tree
  {
      public:
        RookTree() = default;
        RookTree(std::vector<RookAST::Node*> nodes);
        ~RookTree();
        void pushNodes(std::vector<RookAST::Node*> nodes);
        void pushNode(RookAST::Node *node);
        void pushBranch(RookAST::Tree *tree);
        int treeSize();
        void compile(RookVM::PawnExecutor* e);
  };

}

#endif
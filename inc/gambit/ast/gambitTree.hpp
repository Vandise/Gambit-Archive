#ifndef __GAMBIT_TREE_HPP__
#define __GAMBIT_TREE_HPP__ 1

#include "shared/ast/tree.hpp"

namespace Gambit
{

  class Tree : public AST::Tree
  {
      public:
        Tree() = default;
        Tree(std::vector<AST::Node*> nodes);
        ~Tree();
        void pushNodes(std::vector<AST::Node*> nodes);
        void pushNode(AST::Node *node);
        void pushBranch(AST::Tree *tree);
        int treeSize();
        void compile(Compiler::iCodeGenerator *cg);
  };

}

#endif
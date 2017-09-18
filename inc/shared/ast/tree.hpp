#ifndef __AST_TREE
#define __AST_TREE 1

#include <iostream>
#include <vector>

#include "shared/ast/node.hpp"

namespace AST
{

  class Tree : public Node
  {

    public:
      virtual ~Tree(){
        for (auto &n : this->nodes)
        {
          delete(n);
        }
      };
      virtual void pushNodes(std::vector<AST::Node*> nodes) = 0;
      virtual void pushBranch(AST::Tree *tree) = 0;
      virtual void pushNode(AST::Node *node) = 0;
      virtual int treeSize() = 0;
      virtual void compile(Compiler::iCodeGenerator *cg) = 0;

    protected:
      std::vector<AST::Node*> nodes;

  };

}

#endif
#ifndef __ROOK_LABELNODE
#define __ROOK_LABELNODE 1

#include "rook/ast/node.hpp"

namespace RookAST
{

  class LabelNode : public RookAST::Node
  {

    protected:
      std::string label;

    public:

      LabelNode(std::string label);
      ~LabelNode();
      void compile(RookVM::PawnExecutor* e);
      virtual std::string getType();

  };

}

#endif
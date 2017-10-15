#ifndef __ROOK_CALLNODE
#define __ROOK_CALLNODE 1

#include "rook/ast/node.hpp"

#include <vector>

namespace RookAST
{

  class CallNode : public RookAST::Node
  {

    protected:
      std::string methodSignature;
      int parameters;

    public:

      CallNode(std::string methodSignature, int parameters);
      ~CallNode();
      void compile(RookVM::PawnExecutor* e);

  };

}

#endif
#ifndef __GAMBIT_GETLOCALNODE
#define __GAMBIT_GETLOCALNODE 1

#include "shared/ast/node.hpp"

namespace Gambit
{

  class GetLocalNode : public AST::Node
  {

    private:
      std::string identifier;

    public:

      GetLocalNode(std::string identifier, AST::SourceTrace* trace);
      ~GetLocalNode();
      void compile(Compiler::iCodeGenerator *cg);

  };

}

#endif
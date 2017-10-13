#ifndef __GAMBIT_CALLNODE
#define __GAMBIT_CALLNODE 1

#include <vector>
#include "shared/ast/node.hpp"
#include "gambit/ast/arguments.hpp"

namespace Gambit
{

  class CallNode : public AST::Node
  {

    private:
      std::string identifier;
      Gambit::Arguments *arguments;

    public:

      CallNode(std::string identifier, Gambit::Arguments *args, AST::SourceTrace* trace);
      ~CallNode();
      void compile(Compiler::iCodeGenerator *cg);

  };

}

#endif
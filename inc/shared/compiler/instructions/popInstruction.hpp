#ifndef __iMATEINSTRUCTIONPOP
#define __iMATEINSTRUCTIONPOP 1

#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class PopInstruction : public iInstructionSet
  {

    public:


      using Compiler::iInstructionSet::iInstructionSet;

      virtual ~PopInstruction();

      virtual void emit(Compiler::iCodeGenerator *cg);

  };

}

#endif
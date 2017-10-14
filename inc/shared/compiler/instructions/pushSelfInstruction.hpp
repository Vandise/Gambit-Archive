#ifndef __iMATEINSTRUCTIONPUSHSELF
#define __iMATEINSTRUCTIONPUSHSELF 1

#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class PushSelfInstruction : public iInstructionSet
  {

    public:


      using Compiler::iInstructionSet::iInstructionSet;

      virtual ~PushSelfInstruction();

      virtual void emit(Compiler::iCodeGenerator *cg);

  };

}

#endif
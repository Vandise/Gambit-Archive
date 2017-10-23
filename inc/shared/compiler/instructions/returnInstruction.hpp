#ifndef __iMATERETURNISNTRUCTION
#define __iMATERETURNISNTRUCTION 1

#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class ReturnInstruction : public iInstructionSet
  {

    private:
      bool returnedValue;

    public:


      using Compiler::iInstructionSet::iInstructionSet;
      ReturnInstruction(std::string opcode, bool returnedValue);

      virtual ~ReturnInstruction();

      virtual void emit(Compiler::iCodeGenerator *cg);

  };

}

#endif
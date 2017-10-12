#ifndef __iMATEINSTRUCTIONPUSHSTRING
#define __iMATEINSTRUCTIONPUSHSTRING 1

#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class PushStringInstruction : public iInstructionSet
  {

    private:
      std::string value;

    public:


      using Compiler::iInstructionSet::iInstructionSet;
      PushStringInstruction(std::string opcode, std::string value);

      virtual ~PushStringInstruction();

      virtual void emit(Compiler::iCodeGenerator *cg);

  };

}

#endif
#ifndef __COMPILER_INSTRUCTION_EMITTER
#define __COMPILER_INSTRUCTION_EMITTER 1

#include <iostream>

#include "shared/pawn/instructions.hpp"
#include "shared/compiler/iCodeGenerator.hpp"

namespace Compiler
{

  class iCodeGenerator;

  class InstructionEmitter
  {

    private:
      Compiler::iCodeGenerator *cg;

    public:

      InstructionEmitter(Compiler::iCodeGenerator *cg);
      ~InstructionEmitter();
      void pushInteger(int value);

  };

}

#endif
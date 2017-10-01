#ifndef __COMPILER_INSTRUCTION_EMITTER
#define __COMPILER_INSTRUCTION_EMITTER 1

#include <iostream>

#include "shared/ast/sourceTrace.hpp"
#include "shared/pawn/instructions.hpp"
#include "shared/compiler/iCodeGenerator.hpp"
#include "capture/runtime/assignDataTypeMismatch.hpp"


namespace Compiler
{

  class iCodeGenerator;

  class InstructionEmitter
  {

    private:
      Compiler::iCodeGenerator *cg;
      AST::SourceTrace* trace;

    public:

      InstructionEmitter(Compiler::iCodeGenerator *cg);
      ~InstructionEmitter();
      Compiler::InstructionEmitter* withTrace(AST::SourceTrace* trace);
      void pushInteger(int value);
      void setLocal(std::string dataType, std::string identifier, bool isNull = false);

  };

}

#endif
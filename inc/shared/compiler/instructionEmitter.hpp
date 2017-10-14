#ifndef __COMPILER_INSTRUCTION_EMITTER
#define __COMPILER_INSTRUCTION_EMITTER 1

#include <iostream>

#include "shared/ast/sourceTrace.hpp"
#include "shared/pawn/instructions.hpp"
#include "shared/compiler/iCodeGenerator.hpp"
#include "capture/runtime/assignDataTypeMismatch.hpp"
#include "capture/runtime/uselessStatement.hpp"

#include "shared/compiler/instructions/pushStringInstruction.hpp"
#include "shared/compiler/instructions/pushIntegerInstruction.hpp"
#include "shared/compiler/instructions/popInstruction.hpp"
#include "shared/compiler/instructions/setLocalInstruction.hpp"
#include "shared/compiler/instructions/pushSelfInstruction.hpp"
#include "shared/compiler/instructions/callInstruction.hpp"

#define TRACE_PARAMETERS this->trace->filename, this->trace->line, this->trace->column

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
      void pushString(std::string value);
      void setLocal(std::string dataType, std::string identifier, bool isNull = false);
      void pushSelf();
      void call(std::string method, int parameters);

  };

}

#endif
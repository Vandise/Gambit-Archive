#ifndef __COMPILER_INSTRUCTION_EMITTER
#define __COMPILER_INSTRUCTION_EMITTER 1

#include <iostream>

#include <map>

#include "shared/ast/sourceTrace.hpp"
#include "shared/pawn/instructions.hpp"
#include "shared/compiler/iCodeGenerator.hpp"
#include "capture/runtime/assignDataTypeMismatch.hpp"
#include "capture/runtime/uselessStatement.hpp"
#include "capture/runtime/undefinedVariable.hpp"
#include "capture/runtime/undefinedMethod.hpp"

#include "shared/compiler/instructions/pushStringInstruction.hpp"
#include "shared/compiler/instructions/pushIntegerInstruction.hpp"
#include "shared/compiler/instructions/popInstruction.hpp"
#include "shared/compiler/instructions/setLocalInstruction.hpp"
#include "shared/compiler/instructions/pushSelfInstruction.hpp"
#include "shared/compiler/instructions/callInstruction.hpp"
#include "shared/compiler/instructions/getLocalInstruction.hpp"
#include "shared/compiler/instructions/returnInstruction.hpp"

#define TRACE_PARAMETERS this->trace->filename, this->trace->line, this->trace->column

namespace AST
{
  class Node;
}

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
      void getLocal(std::string identifier);
      void pushSelf();
      void call(std::string method, int parameters);
      void defineMethod(std::string name, std::map<std::string, std::string> params, std::string returnType, AST::Node* body);
      void putReturn(bool returnedValue);

  };

}

#endif
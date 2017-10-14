#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/pushSelfInstruction.hpp"

Compiler::PushSelfInstruction::~PushSelfInstruction()
{

};

void
Compiler::PushSelfInstruction::emit(Compiler::iCodeGenerator *cg)
{
  cg->getInstructionBuffer()->emitInstructionLine(this->opCode);
};

#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/popInstruction.hpp"

Compiler::PopInstruction::~PopInstruction()
{

};

void
Compiler::PopInstruction::emit(Compiler::iCodeGenerator *cg)
{
  cg->getInstructionBuffer()->emitInstructionLine(this->opCode);
  cg->getInstructionBuffer()->trackOpCode(this->opCode);
};

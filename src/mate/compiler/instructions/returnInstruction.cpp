#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/returnInstruction.hpp"

Compiler::ReturnInstruction::ReturnInstruction(std::string opcode, bool returnedValue) : iInstructionSet(opcode)
{
  this->returnedValue = returnedValue;
};

Compiler::ReturnInstruction::~ReturnInstruction()
{
  
}

void
Compiler::ReturnInstruction::emit(Compiler::iCodeGenerator *cg)
{
  cg->getInstructionBuffer()->trackOpCode(this->opCode);
  std::string line = this->opCode.append(" ").append(std::to_string(this->returnedValue));
  cg->getInstructionBuffer()->emitInstructionLine(line);
}
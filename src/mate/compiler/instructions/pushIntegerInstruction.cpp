#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/pushIntegerInstruction.hpp"

Compiler::PushIntegerInstruction::PushIntegerInstruction(std::string opcode, std::string value) : iInstructionSet(opcode)
{
  this->value = value;
};

Compiler::PushIntegerInstruction::~PushIntegerInstruction()
{

};

void
Compiler::PushIntegerInstruction::emit(Compiler::iCodeGenerator *cg)
{
  cg->getInstructionBuffer()->emitInstructionLine(
    std::string(this->opCode).append(" ").append(this->value)
  );
  cg->getInstructionBuffer()->trackOpCode(this->opCode);
};
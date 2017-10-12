#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/pushStringInstruction.hpp"

Compiler::PushStringInstruction::PushStringInstruction(std::string opcode, std::string value) : iInstructionSet(opcode)
{
  this->value = value;
};

Compiler::PushStringInstruction::~PushStringInstruction()
{

};

void
Compiler::PushStringInstruction::emit(Compiler::iCodeGenerator *cg)
{
  int offset = cg->getInstructionBuffer()->addLiteral(std::string("\"").append(this->value).append("\""));
  cg->getInstructionBuffer()->emitInstructionLine(
    std::string(this->opCode).append(" ").append(std::to_string(offset))
  );
};
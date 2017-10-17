#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/getLocalInstruction.hpp"

Compiler::GetLocalInstruction::GetLocalInstruction(std::string opcode, std::string identifier) : iInstructionSet(opcode)
{
  this->identifier = identifier;
};

Compiler::GetLocalInstruction::~GetLocalInstruction()
{

};

void
Compiler::GetLocalInstruction::emit(Compiler::iCodeGenerator *cg)
{
  int offset = cg->getInstructionBuffer()->addLiteral(this->identifier);
  cg->getInstructionBuffer()->emitInstructionLine(
    std::string(this->opCode).append(" ").append(std::to_string(offset))
  );
};
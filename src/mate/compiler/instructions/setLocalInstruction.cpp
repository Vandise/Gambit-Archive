#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/setLocalInstruction.hpp"


Compiler::SetLocalInstruction::SetLocalInstruction(std::string opcode, std::string dataType, std::string identifier) : Compiler::iInstructionSet(opcode)
{
  this->dataType = dataType;
  this->identifier = identifier;
};

Compiler::SetLocalInstruction::~SetLocalInstruction()
{

};

void
Compiler::SetLocalInstruction::emit(Compiler::iCodeGenerator *cg)
{
  cg->getInstructionBuffer()->emitInstructionLine(
    std::string(this->opCode).append(" ").append(this->dataType).append(" ").append(this->identifier)
  );
};
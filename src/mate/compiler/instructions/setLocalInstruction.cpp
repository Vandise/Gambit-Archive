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
  // TODO:
  //  idetifier should be an integer offset of literals
  int offset = cg->getInstructionBuffer()->addLiteral(this->identifier);
  cg->getInstructionBuffer()->emitInstructionLine(
    std::string(this->opCode).append(" ").append(this->dataType).append(" ").append(std::to_string(offset))
  );
};
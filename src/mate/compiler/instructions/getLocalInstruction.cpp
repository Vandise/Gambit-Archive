#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/getLocalInstruction.hpp"

Compiler::GetLocalInstruction::GetLocalInstruction(std::string opcode, std::string identifier, bool cloneFlag) : iInstructionSet(opcode)
{
  this->identifier = identifier;
  this->cloneFlag = cloneFlag;
};

Compiler::GetLocalInstruction::~GetLocalInstruction()
{

};

void
Compiler::GetLocalInstruction::emit(Compiler::iCodeGenerator *cg)
{
  cg->getInstructionBuffer()->trackOpCode(this->opCode);
  int offset = cg->getInstructionBuffer()->addLiteral(this->identifier);

  cg->getInstructionBuffer()->emitInstructionLine(
    std::string(this->opCode).append(" ").append(this->cloneFlag ? CLONE_FLAG : "").append(std::to_string(offset))
  );
};
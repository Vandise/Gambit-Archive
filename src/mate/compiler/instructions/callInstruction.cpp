#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/callInstruction.hpp"


Compiler::CallInstruction::CallInstruction(std::string opcode, std::string method, int parameters) : Compiler::iInstructionSet(opcode)
{
  this->method = method;
  this->parameters = parameters;
};

Compiler::CallInstruction::~CallInstruction()
{

};

void
Compiler::CallInstruction::emit(Compiler::iCodeGenerator *cg)
{
  cg->getInstructionBuffer()->trackOpCode(this->opCode);
  cg->getInstructionBuffer()->emitInstructionLine(
    std::string(this->opCode).append(" ").append(this->method).append(" ").append(std::to_string(this->parameters))
  );
};
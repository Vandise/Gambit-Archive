#include "shared/compiler/instructionEmitter.hpp"

Compiler::InstructionEmitter::InstructionEmitter(Compiler::iCodeGenerator *cg)
{
  this->cg = cg;
}

Compiler::InstructionEmitter::~InstructionEmitter()
{
  this->cg = nullptr;
}

void
Compiler::InstructionEmitter::pushInteger(int value)
{
  std::cout << Pawn::Instructions::getInstruction(Pawn::Instructions::PUSH_INTEGER) << " " << value << std::endl;
  if (this->cg->getState() == CS_DEFAULT)
  {
    std::cout << Pawn::Instructions::getInstruction(Pawn::Instructions::POP) << std::endl;
  }
}


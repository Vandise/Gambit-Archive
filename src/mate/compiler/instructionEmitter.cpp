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

void
Compiler::InstructionEmitter::setLocal(std::string dataType, std::string identifier, bool isNull)
{
  std::cout << Pawn::Instructions::getInstruction(Pawn::Instructions::SET_LOCAL) << " " << dataType << " " << identifier << std::endl;
  if (isNull)
  {
    std::cout << "Value: Null" << std::endl;
  }
  else
  {
    std::cout << "TODO: check datatype on stack" << std::endl;
  }
}


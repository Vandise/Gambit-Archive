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

  // Push an integer to the local stack

  Runtime::iStandardClass* integer = this->cg->getRuntime()->getConstant("Integer")->newInstance();
  integer->setInstanceVariable("value", (new Runtime::ValueObject(value)) );

  cg->getFrameStack()->getCurrentFrame()->pushStack(integer);
    integer = nullptr;

  std::cout << Pawn::Instructions::getInstruction(Pawn::Instructions::PUSH_INTEGER) << " " << value << std::endl;
  if (this->cg->getState() == CS_DEFAULT)
  {
    std::cout << Pawn::Instructions::getInstruction(Pawn::Instructions::POP) << std::endl;
      Runtime::iStandardClass* v = cg->getFrameStack()->getCurrentFrame()->popStack();
      delete(v);
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
    // Check value on stack

    Runtime::iStandardClass* integer = cg->getFrameStack()->getCurrentFrame()->popStack();
    Runtime::iPrimitiveDataType *primitive = integer->getInstanceVariable("value")->getValue();

      std::cout << "Class Name: " << integer->getName() << " C++ Value: " << primitive->getInteger() << std::endl;

      delete(integer);
      delete(primitive);
  }
}


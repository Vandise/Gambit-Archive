#include "shared/compiler/instructionEmitter.hpp"

Compiler::InstructionEmitter::InstructionEmitter(Compiler::iCodeGenerator *cg)
{
  this->cg = cg;
}

Compiler::InstructionEmitter::~InstructionEmitter()
{
  this->cg = nullptr;
  this->trace = nullptr;
}

Compiler::InstructionEmitter*
Compiler::InstructionEmitter::withTrace(AST::SourceTrace* trace)
{
  this->trace = trace;
  return this;
}

void
Compiler::InstructionEmitter::pushInteger(int value)
{

  // Push an integer to the local stack

  Runtime::iStandardClass* integer = this->cg->getRuntime()->getConstant("Integer")->newInstance();
  integer->setInstanceVariable("value", (new Runtime::ValueObject(value)) );

  cg->getFrameStack()->getCurrentFrame()->pushStack(integer);
    integer = nullptr;

  this->cg->getInstructionBuffer()->pushInstruction(
    (new Compiler::PushIntegerInstruction( Pawn::Instructions::getInstruction(Pawn::Instructions::PUSH_INTEGER), std::to_string(value) ))
  );

  if (this->cg->getState() == CS_DEFAULT)
  {
    this->cg->getInstructionBuffer()->pushInstruction(
      (new Compiler::PopInstruction( Pawn::Instructions::getInstruction(Pawn::Instructions::POP) ))
    );
      Runtime::iStandardClass* v = cg->getFrameStack()->getCurrentFrame()->popStack();
      std::string name = v->getName();
      delete(v);
    throw Exception::UselessStatement(name, std::to_string(value), TRACE_PARAMETERS);
  }
}

void
Compiler::InstructionEmitter::setLocal(std::string dataType, std::string identifier, bool isNull)
{
  this->cg->getInstructionBuffer()->pushInstruction(
    (new Compiler::SetLocalInstruction(
      Pawn::Instructions::getInstruction(Pawn::Instructions::SET_LOCAL), dataType, identifier ))
  );
  if (isNull)
  {
    std::cout << "Value: Null" << std::endl;
  }
  else
  {
    // Check value on stack
    std::string topStackDataType = cg->getFrameStack()->getCurrentFrame()->peekStack()->getName();
    if (topStackDataType != dataType)
    {
      // TODO: check if parent datatype
      throw Exception::AssignDataTypeMismatch(identifier, dataType, topStackDataType, TRACE_PARAMETERS);
    }
  }
}


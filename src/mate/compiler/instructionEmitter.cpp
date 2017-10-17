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

  //std::cout << "[Instruction]Push Integer" << std::endl;

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

  //std::cout << "[Instruction End]Push Integer" << std::endl;
}

void
Compiler::InstructionEmitter::pushString(std::string value)
{

  //std::cout << "[Instruction]Push String" << std::endl;

  Runtime::iStandardClass* str = this->cg->getRuntime()->getConstant("String")->newInstance();
  str->setInstanceVariable("value", (new Runtime::ValueObject(value)) );

  cg->getFrameStack()->getCurrentFrame()->pushStack(str);
    str = nullptr;

  this->cg->getInstructionBuffer()->pushInstruction(
    (new Compiler::PushStringInstruction( Pawn::Instructions::getInstruction(Pawn::Instructions::PUSH_STRING), value ))
  );

  if (this->cg->getState() == CS_DEFAULT)
  {
    this->cg->getInstructionBuffer()->pushInstruction(
      (new Compiler::PopInstruction( Pawn::Instructions::getInstruction(Pawn::Instructions::POP) ))
    );
      Runtime::iStandardClass* v = cg->getFrameStack()->getCurrentFrame()->popStack();
      std::string name = v->getName();
      delete(v);
    throw Exception::UselessStatement(name, value, TRACE_PARAMETERS);
  }

  //std::cout << "[Instruction End]Push String" << std::endl;
}

void
Compiler::InstructionEmitter::setLocal(std::string dataType, std::string identifier, bool isNull)
{

  //std::cout << "[Instruction]Set Local" << std::endl;

  this->cg->getInstructionBuffer()->pushInstruction(
    (new Compiler::SetLocalInstruction(
      Pawn::Instructions::getInstruction(Pawn::Instructions::SET_LOCAL), dataType, identifier ))
  );

  if (isNull)
  {
    //std::cout << "Value: Null" << std::endl;
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

  cg->getFrameStack()->getCurrentFrame()->setLocal(identifier,
    cg->getFrameStack()->getCurrentFrame()->popStack());

  //std::cout << "[Instruction End]Set Local" << std::endl;
}

void
Compiler::InstructionEmitter::getLocal(std::string identifier)
{

  //std::cout << "[Instruction]Get Local " << identifier << " " << this->cg->getFrameStack()->getCurrentFrame()->hasLocal(identifier) << std::endl;

  if ( this->cg->getFrameStack()->getCurrentFrame()->hasLocal(identifier) )
  {

    //std::cout << "[Instruction]Get Local State" << this->cg->getState() << std::endl;

    if (this->cg->getState() != CS_DEFAULT)
    {
      Runtime::iStandardClass* local = this->cg->getFrameStack()->getCurrentFrame()->getLocal(identifier);

      this->cg->getFrameStack()->getCurrentFrame()->pushStack(local);
        local = nullptr;

      this->cg->getInstructionBuffer()->pushInstruction(
        (new Compiler::GetLocalInstruction( Pawn::Instructions::getInstruction(Pawn::Instructions::GET_LOCAL), identifier))
      );
    }
    else
    {
      throw Exception::UselessStatement("Identifier", identifier, TRACE_PARAMETERS);
    }
  }
  else
  {
    //  TODO:
    //    throw undefined identifier exception
  }

  //std::cout << "[Instruction End]Get Local" << std::endl;
}

void
Compiler::InstructionEmitter::pushSelf()
{

  //std::cout << "[Instruction]Push Self" << std::endl;

  this->cg->getFrameStack()->getCurrentFrame()->pushStack(
    this->cg->getFrameStack()->getCurrentFrame()->getCurrentSelf()
  );

  this->cg->getInstructionBuffer()->pushInstruction(
    (new Compiler::PushSelfInstruction(Pawn::Instructions::getInstruction(Pawn::Instructions::PUSH_SELF)))
  );

  //std::cout << "[Instruction End]Push Self" << std::endl;
}

void
Compiler::InstructionEmitter::call(std::string method, int parameters)
{
  //std::cout << "[Instruction]Call" << std::endl;

  // TODO:
  //  push result for data-type validation

  Runtime::iStandardClass* currentSelf = this->cg->getFrameStack()->getCurrentFrame()->popStack();

  if ( currentSelf->hasMethod(method) )
  {

    for (int i = 0; i < parameters; i++)
    {
      // TODO:
      //    check to see if this object exists in literals
      //    if so, we don't delete it
      this->cg->getFrameStack()->getCurrentFrame()->popStack();
    }

    this->cg->getInstructionBuffer()->pushInstruction(
      (new Compiler::CallInstruction(Pawn::Instructions::getInstruction(Pawn::Instructions::CALL), method, parameters ))
    );

  }
  else
  {
    // TODO:
    //    Method undefined exception
  }
  //std::cout << "[Instruction End]Call" << std::endl;
}



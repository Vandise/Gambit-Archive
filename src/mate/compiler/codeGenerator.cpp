
#include "mate/compiler/codeGenerator.hpp"

Mate::CodeGenerator::CodeGenerator(AST::Tree *t) : Compiler::iCodeGenerator(t)
{
  this->runtime = Runtime::LangRuntime::objectClass;
  this->frameStack = new Compiler::CompilerFrameStack();
  this->frameStack->pushFrame( (new Compiler::CompilerFrame(DEFAULT_FRAME)) );
  this->instructionEmitter = new Compiler::InstructionEmitter( (this) );
}

Mate::CodeGenerator::~CodeGenerator()
{
  this->tree = nullptr;
  delete(this->frameStack);
  this->frameStack = nullptr;
  delete(this->instructionEmitter);
  this->instructionEmitter = nullptr;
  this->runtime = nullptr;
  delete(this->instructionBuffer);
  this->instructionBuffer = nullptr;
}

void
Mate::CodeGenerator::generate(std::string outfile)
{
  this->tree->compile( (this) );
  if ( this->instructionBuffer->peekOpCode() != Pawn::Instructions::getInstruction(Pawn::Instructions::RETURN) )
  {
    this->instructionEmitter->putReturn(false);
  }
  this->instructionBuffer->writeToFile(outfile);
}

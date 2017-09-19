#include "mate/compiler/codeGenerator.hpp"

Mate::CodeGenerator::CodeGenerator(AST::Tree *t) : Compiler::iCodeGenerator(t)
{
  this->frameStack = new Compiler::CompilerFrameStack();
  this->frameStack->pushFrame( (new Compiler::CompilerFrame("MAIN")) );
}

Mate::CodeGenerator::~CodeGenerator()
{
  this->tree = nullptr;
  delete(this->frameStack);
  this->frameStack = nullptr;
}

void
Mate::CodeGenerator::generate()
{
  this->tree->compile( (this) );
  std::cout << "state: " << this->getState() << std::endl;
}


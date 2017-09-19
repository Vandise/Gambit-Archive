#include "mate/compiler/codeGenerator.hpp"

Mate::CodeGenerator::CodeGenerator(AST::Tree *t) : Compiler::iCodeGenerator(t)
{
  this->frameStack = new Compiler::CompilerFrameStack();
  this->frameStack->pushFrame( (new Compiler::CompilerFrame(DEFAULT_FRAME)) );
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
  std::cout << "Current Frame: " << this->frameStack->getCurrentFrame()->getFrameName() << std::endl;

  // TODO: remove test

  Runtime::ValueObject *v = new Runtime::ValueObject(10);
  Runtime::iPrimitiveDataType *t = v->getValue();
  std::cout << t->getType() << " :: " << t->getInteger() << v->getName() << std::endl;

  delete(v);
  delete(t);
}


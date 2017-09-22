#include "mate/compiler/codeGenerator.hpp"

#include "shared/runtime/langRuntime.hpp"
#include "runtime/objectspace/standardClass.hpp"

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

  Runtime::LangRuntime::bootstrap();

    Runtime::iStandardClass* integer = Runtime::LangRuntime::objectClass->getConstant("Integer")->newInstance();
    std::cout << integer->getName() << std::endl;
    delete(integer);

    std::cout << "Class Name: " << Runtime::LangRuntime::objectClass->getName() << " Parent Class: " << Runtime::LangRuntime::objectClass->getSuperClass()->getName() << std::endl;
    std::cout << "Parent Name: " << Runtime::LangRuntime::klass->getName() << " Parent Class: " << Runtime::LangRuntime::klass->getSuperClass()->getName() << std::endl;

  Runtime::LangRuntime::destroy();
}


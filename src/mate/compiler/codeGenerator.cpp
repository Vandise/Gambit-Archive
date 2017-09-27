#include "mate/compiler/codeGenerator.hpp"
#include "shared/runtime/langRuntime.hpp"

Mate::CodeGenerator::CodeGenerator(AST::Tree *t) : Compiler::iCodeGenerator(t)
{
  this->instructionEmitter = new Compiler::InstructionEmitter( (this) );
  this->frameStack = new Compiler::CompilerFrameStack();
  this->frameStack->pushFrame( (new Compiler::CompilerFrame(DEFAULT_FRAME)) );
}

Mate::CodeGenerator::~CodeGenerator()
{
  this->tree = nullptr;
  delete(this->frameStack);
  this->frameStack = nullptr;
  delete(this->instructionEmitter);
  this->instructionEmitter = nullptr;
}

void
Mate::CodeGenerator::generate()
{
  this->tree->compile( (this) );
  /*
  std::cout << "Current Frame: " << this->frameStack->getCurrentFrame()->getFrameName() << std::endl;


    //Runtime::iStandardClass* integer = Runtime::LangRuntime::objectClass->getConstant("Integer")->newInstance();
    (this->frameStack->getCurrentFrame())->pushStack(Runtime::LangRuntime::objectClass->getConstant("Integer")->newInstance());

    Runtime::iStandardClass* integer = this->frameStack->getCurrentFrame()->popStack();
    std::cout << integer->getName() << std::endl;
    std::cout << this->frameStack->getCurrentFrame()->getCurrentSelf()->getName() << std::endl;
    delete(integer);

    std::cout << "Class Name: " << Runtime::LangRuntime::objectClass->getName() << " Parent Class: " << Runtime::LangRuntime::objectClass->getSuperClass()->getName() << std::endl;
    std::cout << "Parent Name: " << Runtime::LangRuntime::klass->getName() << " Parent Class: " << Runtime::LangRuntime::klass->getSuperClass()->getName() << std::endl;
  */
}


#include "rook/ast/tree.hpp"
#include "rook/vm/pawnExecutor.hpp"


RookVM::PawnExecutor::PawnExecutor(RookAST::Tree *tree)
{
  this->runtime = Runtime::LangRuntime::objectClass;
  this->frameStack = new VM::iFrameStack();
  this->frameStack->pushFrame( (new VM::iFrame(DEFAULT_FRAME)) );
  this->tree = tree;
};

RookVM::PawnExecutor::~PawnExecutor()
{
  delete(this->tree);
  delete(this->frameStack);
}

void
RookVM::PawnExecutor::run()
{
  this->tree->compile( (this) );
}

Runtime::iStandardClass*
RookVM::PawnExecutor::getRuntime()
{
  return this->runtime;
}

VM::iFrameStack*
RookVM::PawnExecutor::getFrameStack()
{
  return this->frameStack;
}
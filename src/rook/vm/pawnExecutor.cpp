#include "rook/ast/tree.hpp"
#include "rook/vm/pawnExecutor.hpp"


RookVM::PawnExecutor::PawnExecutor(RookAST::Tree *tree)
{
  this->runtime = Runtime::LangRuntime::objectClass;
  this->frameStack = new VM::iFrameStack();
  this->frameStack->pushFrame( (new VM::iFrame(DEFAULT_FRAME)) );
  this->literalsTable = new RookVM::LiteralsTable();
  this->tree = tree;
};

RookVM::PawnExecutor::~PawnExecutor()
{
  delete(this->tree);
  delete(this->frameStack);
  delete(this->literalsTable);
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

RookVM::LiteralsTable*
RookVM::PawnExecutor::getLiteralsTable()
{
  return this->literalsTable;
}

void
RookVM::PawnExecutor::incrementNodePointer()
{
  this->currentNode += 1;
}

void
RookVM::PawnExecutor::setNodePointer(int value)
{
  this->currentNode = value;
}

int
RookVM::PawnExecutor::getNodePointer()
{
  return this->currentNode;
}

void
RookVM::PawnExecutor::addLabel(std::string label)
{
  std::cout << label << " at position: " << this->getNodePointer() << std::endl;
  this->labels[label] = this->getNodePointer();
}

void
RookVM::PawnExecutor::jumpToLabel(std::string label)
{
  int point = this->labels[label];
  this->setNodePointer(point);
}




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
  this->frameStack->getCurrentFrame()->incrementNodePointer();
}

void
RookVM::PawnExecutor::setNodePointer(int value)
{
  this->frameStack->getCurrentFrame()->setNodePointer(value);
}

int
RookVM::PawnExecutor::getNodePointer()
{
  return this->frameStack->getCurrentFrame()->getNodePointer();
}

bool
RookVM::PawnExecutor::hasLabel(std::string label)
{
  return (this->labels.count(label) > 0);
}

void
RookVM::PawnExecutor::addLabel(std::string label)
{
  Dev::Board::sendMessage(
    std::string("LOG|Label ").append(label).append(" added at position: ").append(std::to_string(this->getNodePointer()))
  );
  this->labels[label] = this->getNodePointer();
}

void
RookVM::PawnExecutor::jumpToLabel(std::string label)
{
  int point = this->labels[label];
  this->frameStack->getCurrentFrame()->setNodePointer(point);
}

int
RookVM::PawnExecutor::labelSize()
{
  return this->labels.size();
}

std::map<std::string, int>
RookVM::PawnExecutor::getLabels()
{
  return this->labels;
}

void
RookVM::PawnExecutor::terminate()
{
  this->terminated = true;
  Dev::Board::sendMessage(std::string("LOG|RookVM terminated"));
}

bool
RookVM::PawnExecutor::isTerminated()
{
  return this->terminated;
}




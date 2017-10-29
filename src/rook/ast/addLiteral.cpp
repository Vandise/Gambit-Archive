#include "rook/ast/addLiteral.hpp"

RookAST::AddLiteralNode::AddLiteralNode(std::string literal)
{
  this->literal = literal;
}

RookAST::AddLiteralNode::~AddLiteralNode()
{
  
}

void
RookAST::AddLiteralNode::compile(RookVM::PawnExecutor* e)
{
  e->getLiteralsTable()->addLiteral(this->literal);
    Dev::Board::sendMessage(std::string("LOG|Literal ").append(this->literal).append(" added"));
  e->incrementNodePointer();
}
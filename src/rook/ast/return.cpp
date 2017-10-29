#include "rook/ast/return.hpp"

RookAST::ReturnNode::ReturnNode(int popStack)
{
  this->popStack = popStack;
}

RookAST::ReturnNode::~ReturnNode()
{
  
}

void
RookAST::ReturnNode::compile(RookVM::PawnExecutor* e)
{
  //
  // Are we on the main frame and returning?
  //
  std::string frameName = e->getFrameStack()->getCurrentFrame()->getFrameName();
  if ( e->getFrameStack()->stackSize() == 1 )
  {
    e->terminate();
  }
  else
  {
    //
    // We are not on the main frame
    // and need to move a return value to the parent frame
    //
    if ( popStack > 0)
    {
      // TODO:
      //  get current frame and pop a value

      // remove the frame
      Dev::Board::sendMessage(std::string("LOG|Return"));
      Dev::Board::sendMessage(std::string("LOG|Pop frame"));
      Dev::Board::sendMessage(std::string("POP_FRAME|").append(frameName));
      e->getFrameStack()->popFrame();

      // TODO:
      //  push new value to current frame
    }
    else
    {
      std::cout << "Compile RETURN " << " " << std::endl;
      //
      // No return value and not on main frame
      //
      Dev::Board::sendMessage(std::string("LOG|Return"));
      Dev::Board::sendMessage(std::string("LOG|Pop frame"));
      Dev::Board::sendMessage(std::string("POP_FRAME|pop"));
      e->getFrameStack()->popFrame();
    }
  }
  e->incrementNodePointer();
}

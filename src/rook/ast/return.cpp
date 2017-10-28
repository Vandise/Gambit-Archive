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
  if ( e->getFrameStack()->stackSize() == 1 )
  {
    std::cout << "Compile RETURN " << " terminate main frame" << std::endl;
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
      std::cout << "Compile RETURN " << " return value" << std::endl;
      // TODO:
      //  get current frame and pop a value

      // remove the frame
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
      e->getFrameStack()->popFrame();
    }
  }
  e->incrementNodePointer();
}

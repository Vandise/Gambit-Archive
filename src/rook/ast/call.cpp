#include "rook/ast/call.hpp"

RookAST::CallNode::CallNode(std::string methodSignature, int parameters)
{
  this->methodSignature = methodSignature;
  this->parameters = parameters;
}

RookAST::CallNode::~CallNode()
{
  
}

void
RookAST::CallNode::compile(RookVM::PawnExecutor* e)
{
  std::cout << "Compiling CALL: " << methodSignature << " " << parameters << std::endl;

  //
  // Set up current method frame
  //  top-of-stack is the current object
  //
  VM::iFrame *f = new VM::iFrame(this->methodSignature);
  f->setCurrentSelf(
    e->getFrameStack()->getCurrentFrame()->popStack()
  );

  //
  //  Clone parameters from parent stack
  //
  for (int i = 0; i < this->parameters; i++)
  {
    f->pushStack(
      e->getFrameStack()->getCurrentFrame()->popStack()
    );
  }

  //
  //  push the frame onto the stack
  //
  e->getFrameStack()->pushFrame(f);

  //
  // Call the method
  //
  e->getFrameStack()->getCurrentFrame()->getCurrentSelf()->lookup(this->methodSignature)->call(
     e->getFrameStack()->getCurrentFrame()->getCurrentSelf(),
      e->getFrameStack()->getCurrentFrame()->getLocalStack()
  );

  //
  // Clean up memory
  //
  e->getFrameStack()->popFrame();

  e->incrementNodePointer();
}

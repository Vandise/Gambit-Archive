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
  // cache current node position
  //  in case of label transition
  //
  int nodePosition = e->getFrameStack()->getCurrentFrame()->getNodePointer();

  //
  // Set up current method frame
  //  top-of-stack is the current object
  //
  VM::iFrame *f = new VM::iFrame(this->methodSignature);
  f->setCurrentSelf(
    e->getFrameStack()->getCurrentFrame()->popStack()
  );
  f->setNodePointer(nodePosition);

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

  if ( e->hasLabel(this->methodSignature) )
  {
    //
    // User defined method
    //
      std::cout << "Transitioning to label: " << this->methodSignature << std::endl;
      e->jumpToLabel(methodSignature);
    // Note:
    //  On return node, it will clear and remove the frame
    //  then return to the original node position + 1
  }
  else
  {
    //
    // Native Methods
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

}

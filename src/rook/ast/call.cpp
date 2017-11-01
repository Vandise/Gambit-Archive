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

  Dev::Board::sendMessage(std::string("LOG|Calling method ").append(this->methodSignature));

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

  Dev::Board::sendMessage(std::string("POP_STACK|self"));

  //
  //  Clone parameters from parent stack
  //
  for (int i = 0; i < this->parameters; i++)
  {
    f->pushStack(
      e->getFrameStack()->getCurrentFrame()->popStack()
    );
    Dev::Board::sendMessage(std::string("POP_STACK|param_").append(std::to_string(i)));
  }

  //
  //  push the frame onto the stack
  //
  e->getFrameStack()->pushFrame(f);
  Dev::Board::sendMessage(std::string("LOG|Frame ").append(this->methodSignature).append(" added to the Frame Stack"));
  Dev::Board::sendMessage(std::string("PUSH_FRAME|").append(this->methodSignature));

  // Debug, TODO: add _DEBUG flag check
  std::vector<Runtime::iStandardClass*> stack = f->getLocalStack();
  for (int i = 0; i < this->parameters; i++)
  {
    Dev::Board::sendMessage(std::string("PUSH_STACK|").append(Dev::Board::formatClassMsg(stack[i])));
  }

  //
  // Call the method
  //

  if ( e->hasLabel(this->methodSignature) )
  {
    //
    // User defined method
    //
      Dev::Board::sendMessage(std::string("LOG|Jump to label ").append(this->methodSignature));
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
    Dev::Board::sendMessage(std::string("LOG|Call native method ").append(this->methodSignature));
    e->getFrameStack()->getCurrentFrame()->getCurrentSelf()->lookup(this->methodSignature)->call(
       e->getFrameStack()->getCurrentFrame()->getCurrentSelf(),
        e->getFrameStack()->getCurrentFrame()->getLocalStack()
    );

    //
    // Clean up memory
    //
    Dev::Board::sendMessage(std::string("LOG|Pop frame"));
    Dev::Board::sendMessage(std::string("POP_FRAME|").append(this->methodSignature));
    e->getFrameStack()->popFrame();

    e->incrementNodePointer();
  }

}

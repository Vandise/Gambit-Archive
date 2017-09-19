#ifndef __COMPILERFRAME
#define __COMPILERFRAME 1

#include "shared/vm/frame/iFrame.hpp"

namespace Compiler
{

  class CompilerFrame : public VM::iFrame
  {
    using VM::iFrame::iFrame;
    virtual ~CompilerFrame(){};
  };

}

#endif
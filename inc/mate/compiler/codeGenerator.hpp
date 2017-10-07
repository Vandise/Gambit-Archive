#ifndef __MATECODEGENERATOR
#define __MATECODEGENERATOR 1

#define DEFAULT_FRAME "MAIN"

#include <iostream>
#include <string>

#include "dev/debugnew/debug_new.h"
#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/ast/tree.hpp"
#include "compiler/frame/compilerFrameStack.hpp"

// TODO: remove valueobject header
#include "runtime/objectspace/valueObject.hpp"

namespace Mate
{

  class CodeGenerator : public Compiler::iCodeGenerator
  {

    public:
      CodeGenerator(AST::Tree *tree);
      ~CodeGenerator();
      void generate(std::string outfile);

  };

}

#endif
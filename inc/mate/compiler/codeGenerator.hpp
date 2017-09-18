#ifndef __MATECODEGENERATOR
#define __MATECODEGENERATOR 1

#include <iostream>
#include <string>

#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/ast/tree.hpp"

namespace Mate
{

  class CodeGenerator : public Compiler::iCodeGenerator
  {

    public:
      using Compiler::iCodeGenerator::iCodeGenerator;
      ~CodeGenerator();
      void generate();
      void setState(std::string s);

  };

}

#endif
#ifndef __iMATEINSTRUCTIONGETLOCAL
#define __iMATEINSTRUCTIONGETLOCAL 1

#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class GetLocalInstruction : public iInstructionSet
  {

    private:
      std::string identifier;
      bool cloneFlag;

    public:


      using Compiler::iInstructionSet::iInstructionSet;
      GetLocalInstruction(std::string opcode, std::string identifier, bool cloneFlag);

      virtual ~GetLocalInstruction();

      virtual void emit(Compiler::iCodeGenerator *cg);

  };

}

#endif
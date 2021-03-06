#ifndef __iMATEINSTRUCTIONSETLOCAL
#define __iMATEINSTRUCTIONSETLOCAL 1

#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class SetLocalInstruction : public iInstructionSet
  {

    private:
      std::string identifier;
      std::string dataType;

    public:


      using Compiler::iInstructionSet::iInstructionSet;
      SetLocalInstruction(std::string opcode, std::string dataType, std::string identifier);

      virtual ~SetLocalInstruction();

      virtual void emit(Compiler::iCodeGenerator *cg);

  };

}

#endif
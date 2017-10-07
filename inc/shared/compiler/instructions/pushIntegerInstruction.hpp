#ifndef __iMATEINSTRUCTIONPUSHINTEGER
#define __iMATEINSTRUCTIONPUSHINTEGER 1

#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class PushIntegerInstruction : public iInstructionSet
  {

    private:
      std::string value;

    public:


      using Compiler::iInstructionSet::iInstructionSet;
      PushIntegerInstruction(std::string opcode, std::string value) : iInstructionSet(opcode)
      {
        this->value = value;
      };

      virtual ~PushIntegerInstruction()
      {

      };

      virtual void emit(Compiler::iCodeGenerator *cg)
      {
        std::cout << this->opCode << " " << this->value << std::endl;
      };

  };

}

#endif
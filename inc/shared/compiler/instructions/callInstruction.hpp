#ifndef __iMATEINSTRUCTIONCALL
#define __iMATEINSTRUCTIONCALL 1

#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class CallInstruction : public iInstructionSet
  {

    protected:
      std::string method;
      int parameters;

    public:


      using Compiler::iInstructionSet::iInstructionSet;
      CallInstruction(std::string opcode, std::string method, int parameters);

      virtual ~CallInstruction();

      virtual void emit(Compiler::iCodeGenerator *cg);

  };

}

#endif
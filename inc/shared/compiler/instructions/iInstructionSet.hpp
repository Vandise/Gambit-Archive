#ifndef __iMATEINSTRUCTIONSET
#define __iMATEINSTRUCTIONSET 1

#include <iostream>

namespace Compiler
{

  class iCodeGenerator;

  class iInstructionSet
  {

    protected:
      std::string opCode;

    public:

      iInstructionSet(std::string opCode)
      {
        this->opCode = opCode;
      };

      virtual ~iInstructionSet()
      {

      };

      virtual void emit(Compiler::iCodeGenerator *cg) = 0;

  };

}

#endif
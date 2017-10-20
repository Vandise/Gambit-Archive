#ifndef __MATEINSTRUCTIONBUFFER
#define __MATEINSTRUCTIONBUFFER 1

#include <fstream>
#include <string>
#include <vector>

#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class InstructionBuffer
  {

    protected:

      std::string outBuffer;
      std::string instructionBuffer;
      std::string methodBuffer;
      std::vector<std::string> literals;
      std::vector<Compiler::iInstructionSet*> instructions;
      Compiler::iCodeGenerator *cg;

    public:

      InstructionBuffer(Compiler::iCodeGenerator *cg);

      virtual ~InstructionBuffer();

      virtual void pushInstruction(Compiler::iInstructionSet* instruction);

      virtual Compiler::iInstructionSet* popInstruction();

      virtual int addLiteral(std::string literal);

      virtual void emitLabelLine(std::string label);

      virtual void emitInstructionLine(std::string instruction);

      virtual void writeToFile(std::string filename, Compiler::iCodeGenerator *cg);

  };

}

#endif
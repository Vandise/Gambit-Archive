#ifndef __MATEINSTRUCTIONBUFFER
#define __MATEINSTRUCTIONBUFFER 1

#include <deque>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/iInstructionSet.hpp"

#define MAX_DEQUE_TRACE_SIZE 10

namespace Compiler
{

  class InstructionBuffer
  {

    protected:

      std::string outBuffer;
      std::string instructionBuffer;
      std::string methodBuffer;
      std::vector<std::string> methodSignatures;
      std::vector<std::string> literals;
      std::deque<std::string> traceOpCode;
      std::vector<Compiler::iInstructionSet*> instructions;
      Compiler::iCodeGenerator *cg;

    public:

      InstructionBuffer(Compiler::iCodeGenerator *cg);

      virtual ~InstructionBuffer();

      virtual void pushInstruction(Compiler::iInstructionSet* instruction);

      virtual Compiler::iInstructionSet* popInstruction();

      virtual int addLiteral(std::string literal);

      virtual void emitLabelLine(std::string label);

      virtual void trackOpCode(std::string opCode);
      virtual std::string peekOpCode(int offset = 0);

      virtual bool hasMethodSignature(std::string sig);
      virtual void addMethodSignature(std::string sig);

      virtual void emitInstructionLine(std::string instruction);

      virtual void writeToFile(std::string filename);

  };

}

#endif
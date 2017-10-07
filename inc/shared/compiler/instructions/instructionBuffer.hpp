#ifndef __MATEINSTRUCTIONBUFFER
#define __MATEINSTRUCTIONBUFFER 1

#include <string>
#include <vector>

#include "shared/compiler/iCodeGenerator.hpp"
#include "shared/compiler/instructions/iInstructionSet.hpp"

namespace Compiler
{

  class InstructionBuffer
  {

    protected:

      std::vector<std::string> literals;
      std::vector<Compiler::iInstructionSet*> instructions;

    public:

      InstructionBuffer() = default;

      virtual ~InstructionBuffer()
      {
        std::vector<Compiler::iInstructionSet*>::iterator it;
        for( it = this->instructions.begin(); it != this->instructions.end(); it++ )
        {
          delete(*it);
        }
      };

      virtual void pushInstruction(Compiler::iInstructionSet* instruction)
      {
        this->instructions.push_back(instruction);
      };

      virtual Compiler::iInstructionSet* popInstruction()
      {
        Compiler::iInstructionSet* i = this->instructions.back();
          this->instructions.pop_back();
        return i;
      };

      virtual int addLiteral(std::string literal)
      {
        auto pred = [literal](std::string & search)
        {
          return search == literal;
        };
        auto index = std::find_if(this->literals.begin(), this->literals.end(), pred);
        if(index != this->literals.end())
        {
          return index - this->literals.begin();
        }
        this->literals.push_back(literal);
        return this->literals.size() - 1;
      };

      virtual void writeToFile(std::string filename, Compiler::iCodeGenerator *cg)
      {
        std::vector<Compiler::iInstructionSet*>::iterator it;
        for( it = this->instructions.begin(); it != this->instructions.end(); it++ )
        {
          (*it)->emit(cg);
        }
      };

  };

}

#endif
#include "mate/compiler/codeGenerator.hpp"
#include "shared/compiler/instructions/instructionBuffer.hpp"

Compiler::InstructionBuffer::InstructionBuffer(Compiler::iCodeGenerator *cg)
{
  this->cg = cg;
}

Compiler::InstructionBuffer::~InstructionBuffer()
{
  /*
  std::vector<Compiler::iInstructionSet*>::iterator it;
  for( it = this->instructions.begin(); it != this->instructions.end(); it++ )
  {
    delete(*it);
  }
  */
}

void
Compiler::InstructionBuffer::pushInstruction(Compiler::iInstructionSet* instruction)
{
  //this->instructions.push_back(instruction);
  instruction->emit(this->cg);
  delete(instruction);
}

Compiler::iInstructionSet*
Compiler::InstructionBuffer::popInstruction()
{
  Compiler::iInstructionSet* i = this->instructions.back();
    this->instructions.pop_back();
  return i;
}

int
Compiler::InstructionBuffer::addLiteral(std::string literal)
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
}

void
Compiler::InstructionBuffer::emitLabelLine(std::string label)
{
  std::string labelLine = std::string(".").append(label).append("\n");
  if (!cg->hasState(CS_METHOD))
  {
    this->instructionBuffer.append(labelLine);
  }
  else
  {
    this->methodBuffer.append(labelLine);
  }
}

void
Compiler::InstructionBuffer::emitInstructionLine(std::string instruction)
{
  std::string line = std::string("\t").append(instruction).append("\n");

  if (!cg->hasState(CS_METHOD))
  {
    this->instructionBuffer.append(line);
  }
  else
  {
    this->methodBuffer.append(line);
  }
}

void
Compiler::InstructionBuffer::writeToFile(std::string filename)
{
  /*
  std::vector<Compiler::iInstructionSet*>::iterator it;
  for( it = this->instructions.begin(); it != this->instructions.end(); it++ )
  {
    (*it)->emit(this->cg);
  }
  */
  if (!this->instructionBuffer.empty())
  {

    this->outBuffer.append(".literals\n");
      std::vector<std::string>::iterator it;
      for( it = this->literals.begin(); it != this->literals.end(); it++ )
      {
        this->outBuffer.append("\t").append(*it).append("\n");
      }
    this->outBuffer.append(".code\n");
      this->outBuffer.append(this->instructionBuffer);

    if(!this->methodBuffer.empty())
    {
      std::cout << "Method buffer: " << std::endl << this->methodBuffer << std::endl;
      this->outBuffer.append(this->methodBuffer);
    }

    std::ofstream out(filename);
      out << this->outBuffer;
    out.close();
  }
}
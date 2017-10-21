#ifndef __iMATECODEGENERATOR
#define __iMATECODEGENERATOR 1

#include <algorithm>
#include <string>

#include "shared/runtime/langRuntime.hpp"
#include "shared/compiler/compilerState.hpp"
#include "shared/vm/frame/iFrameStack.hpp"
#include "shared/compiler/instructionEmitter.hpp"
#include "shared/compiler/instructions/instructionBuffer.hpp"

namespace AST
{
  class Tree;
}

namespace Compiler
{

  class InstructionEmitter;

  class iCodeGenerator
  {

    protected:

      AST::Tree *tree;
      Runtime::iStandardClass* runtime;
      VM::iFrameStack *frameStack;
      Compiler::InstructionEmitter *instructionEmitter;
      Compiler::InstructionBuffer *instructionBuffer;
      COMPILERSTATE defaultState = CS_DEFAULT;
      std::vector<COMPILERSTATE> stateStack;

    public:

      iCodeGenerator(AST::Tree *tree)
      {
        this->tree = tree;
        this->instructionBuffer = new Compiler::InstructionBuffer( (this) );
      };

      virtual ~iCodeGenerator() = default;
      virtual void generate(std::string outfile) = 0;

      virtual void setState(COMPILERSTATE state)
      {
        this->stateStack.push_back(state);
      };

      virtual void popState()
      {
        if (!this->stateStack.empty())
        {
          this->stateStack.pop_back();
        }
      };

      virtual bool hasState(COMPILERSTATE state)
      {
        if( std::find( this->stateStack.begin(), this->stateStack.end(), state) != this->stateStack.end() )
        {
          return true;
        }
        return false;
      };

      virtual COMPILERSTATE getState()
      {
        if (this->stateStack.empty())
        {
          return this->defaultState;
        }
        return this->stateStack.back();
      };

      virtual Compiler::InstructionEmitter* emit()
      {
        return this->instructionEmitter;
      };

      virtual Runtime::iStandardClass* getRuntime()
      {
        return this->runtime;
      };

      virtual Compiler::InstructionBuffer* getInstructionBuffer()
      {
        return this->instructionBuffer;
      };

      virtual VM::iFrameStack* getFrameStack()
      {
        return this->frameStack;
      };

  };

}

#endif
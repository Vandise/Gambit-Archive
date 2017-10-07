#ifndef __iMATECODEGENERATOR
#define __iMATECODEGENERATOR 1

#include <string>
#include <stack>

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
      std::stack<COMPILERSTATE> stateStack;

    public:

      iCodeGenerator(AST::Tree *tree)
      {
        this->tree = tree;
        this->instructionBuffer = new Compiler::InstructionBuffer();
      };

      virtual ~iCodeGenerator() = default;
      virtual void generate(std::string outfile) = 0;

      virtual void setState(COMPILERSTATE state)
      {
        this->stateStack.push(state);
      };

      virtual void popState()
      {
        if (!this->stateStack.empty())
        {
          this->stateStack.pop();
        }
      };

      virtual COMPILERSTATE getState()
      {
        if (this->stateStack.empty())
        {
          return this->defaultState;
        }
        return this->stateStack.top();
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
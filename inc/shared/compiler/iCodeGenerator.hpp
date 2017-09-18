#ifndef __iMATECODEGENERATOR
#define __iMATECODEGENERATOR 1

#include <string>
#include <stack>

#include "shared/compiler/compilerState.hpp"

namespace AST
{
  class Tree;
}

namespace Compiler
{

  class iCodeGenerator
  {
    protected:
      AST::Tree *tree;
      COMPILERSTATE defaultState = CS_DEFAULT;
      std::stack<COMPILERSTATE> stateStack;

    public:
      iCodeGenerator(AST::Tree *tree)
      {
        this->tree = tree;
      };
      virtual ~iCodeGenerator() = default;
      virtual void generate() = 0;
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
  };

}

#endif
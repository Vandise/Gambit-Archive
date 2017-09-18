#ifndef __iMATECODEGENERATOR
#define __iMATECODEGENERATOR 1

#include <string>

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
      std::string state;

    public:
      iCodeGenerator(AST::Tree *tree)
      {
        this->tree = tree;
      };
      virtual ~iCodeGenerator() = default;
      virtual void generate() = 0;
      virtual void setState(std::string s) = 0;
  };

}

#endif
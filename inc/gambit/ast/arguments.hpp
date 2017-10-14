#ifndef __GAMBIT_ARGUMENTS_AST
#define __GAMBIT_ARGUMENTS_AST 1

#include <vector>
#include "shared/ast/node.hpp"

namespace Gambit
{

  class Arguments
  {

    private:
      std::vector<AST::Node *> args;

    public:

      Arguments()
      {

      };

      virtual ~Arguments()
      {
        std::vector<AST::Node *>::iterator it;
        for(it = this->args.begin(); it != this->args.end(); it++)
        {
          delete(*it);
        }
        this->args.clear();
      };

      void add(AST::Node *arg)
      {
        this->args.push_back(arg);
      };

      std::vector<AST::Node *> getArgs()
      {
        return this->args;
      };

  };

}

#endif
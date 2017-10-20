#ifndef __GAMBIT_PARAMETERS_AST
#define __GAMBIT_PARAMETERS_AST 1

#include <map>
#include "shared/ast/node.hpp"

namespace Gambit
{

  class Parameters
  {

    private:
      std::map<std::string, std::string> params;

    public:

      Parameters()
      {

      };

      virtual ~Parameters()
      {
        this->params.clear();
      };

      void add(std::string idenfitifer, std::string type)
      {
        this->params[idenfitifer] = type;
      };

      std::map<std::string, std::string> getParams()
      {
        return this->params;
      };

  };

}

#endif
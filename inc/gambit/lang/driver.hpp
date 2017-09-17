#ifndef __GAMBIT_DRIVER_HPP__
#define __GAMBIT_DRIVER_HPP__ 1

#include <cctype>
#include <fstream>
#include <cassert>

#include "dev/debugnew/debug_new.h"
#include "shared/lang/iDriver.hpp"
#include "gambit/ast/ast.hpp"
#include "gambit/scanner.hpp"
#include "gambit/parser.tab.hpp"

namespace Gambit
{

  class Driver : public Extensions::iDriver
  {

    public:

      Driver();
      virtual ~Driver();
      AST::Tree* getTree();
      int parse( const char *filename );

    private:

      Gambit::Tree *tree;
      Gambit::Parser  *parser  = nullptr;
      Gambit::Scanner *scanner = nullptr;

  };

}

#endif
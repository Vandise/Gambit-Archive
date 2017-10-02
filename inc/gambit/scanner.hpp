#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
  #include <FlexLexer.h>
  #include <fstream>
#endif

#include <string>
#include "gambit/parser.tab.hpp"
#include "gambit/location.hh"

namespace Gambit {

  class Scanner : public yyFlexLexer
  {

    private:

      std::string filename;

      Gambit::Parser::semantic_type *yylval = nullptr;
      Gambit::Parser::location_type *loc    = nullptr;

    public:

      Scanner(std::istream *in, std::string filename) : yyFlexLexer(in)
      {
        this->filename = filename;
        loc = new Gambit::Parser::location_type();
      };

      virtual std::string getFileName()
      {
        return this->filename;
      };

      virtual ~Scanner()
      {
        delete(loc);
      };

      using FlexLexer::yylex;
      virtual int yylex( Gambit::Parser::semantic_type * const lval, Gambit::Parser::location_type *location );

  };

}

#endif
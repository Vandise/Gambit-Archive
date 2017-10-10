#ifndef __ROOKSCANNER_HPP__
#define __ROOKSCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
  #include <FlexLexer.h>
  #include <fstream>
#endif

#include <string>
#include "rook/parser.tab.hpp"
#include "rook/location.hh"

namespace Rook {

  class Scanner : public yyFlexLexer
  {

    private:

      std::string filename;

      Rook::Parser::semantic_type *yylval = nullptr;
      Rook::Parser::location_type *loc    = nullptr;

    public:

      Scanner(std::istream *in, std::string filename) : yyFlexLexer(in)
      {
        this->filename = filename;
        loc = new Rook::Parser::location_type();
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
      virtual int yylex( Rook::Parser::semantic_type * const lval, Rook::Parser::location_type *location );

  };

}

#endif
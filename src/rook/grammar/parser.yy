%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Rook}
%define parser_class_name {Parser}
%define parse.error verbose

%code requires {

  #include <vector>
  #include <string>
  #include <iostream>
  #include "dev/debugnew/debug_new.h"

  namespace Rook {
    class Scanner;
  }

  namespace Extensions {
    class iDriver;
  }

  namespace AST {
    class Node;
    class Tree;
  }

}

%parse-param { Rook::Scanner &scanner }

%code {

  #include "rook/scanner.hpp"
  #include "capture/parsing/unexpectedToken.hpp"

  #undef yylex
  #define yylex scanner.yylex

  #define SOURCE_LINE yylhs.location.begin.line
  #define SOURCE_COLUMN yylhs.location.end.column
  #define SOURCE_FILE scanner.getFileName()

  using namespace std;
}

%locations
%initial-action
{
  std::string f("initial file");
  @$.begin.filename = @$.end.filename = &f;
};

%token                   END          0  "end of file"
%token                   T_NEWLINE

%union {
  int ival;
  std::string *sval;
}

%%

root:
  END
  | Expressions END                     {  }
  ;

Expressions:
  Expression                          {

                                      }
  | Expressions Terminator Expression {

                                      }

  | Expressions Terminator            {  }
  ;

Expression:
    Instructions
  ;

Instructions:

  ;

Terminator:
    T_NEWLINE
  ;

%%


void
Rook::Parser::error(const location_type& l, const std::string& m )
{
  throw Exception::UnexpectedToken(m, SOURCE_FILE, l.begin.line, l.end.column);
}
%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Gambit}
%define parser_class_name {Parser}

%code requires {

  #include <vector>
  #include <string>
  #include "dev/debugnew/debug_new.h"

  namespace Gambit {
    class Scanner;
  }

  namespace Extensions {
    class iDriver;
  }
}

%parse-param { Gambit::Scanner &scanner }
%parse-param { Extensions::iDriver  &driver  }

%code {

  #include "gambit/lang/driver.hpp"
  #include "gambit/scanner.hpp"

  #undef yylex
  #define yylex scanner.yylex

}

%locations

%token                   END          0  "end of file"
%token       <ival>      T_INTEGER
%token       <sval>      T_STRING
%token       <sval>      T_CONSTANT
%token       <sval>      T_IDENTIFIER
%token                   T_BIND
%token                   T_ASSIGN
%token                   T_OPEN_BRACKET
%token                   T_CLOSE_BRACKET
%token                   T_COMMA
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
  Expression                        {

                                      
                                    }
  | Expressions Terminator Expression {

                                      }

  | Expressions Terminator          {  }
  ;

Expression:
    Literals
  | LocalDefinition
  | Array
  ;

Literals:
  T_INTEGER                           {

                                      }
  | T_STRING                          {

                                      }
  ;

LocalDefinition:
    T_CONSTANT T_BIND T_IDENTIFIER    {

                                      }
  | T_CONSTANT T_BIND T_IDENTIFIER T_ASSIGN Expression   
                                      {

                                      }
  ;

Array:
  T_OPEN_BRACKET Parameters T_CLOSE_BRACKET {

                                              }
  ;

Parameters:
    Expression                      {

                                    }
  | Parameters T_COMMA Expression   {

                                    }
  |                                 {

                                    }
  ;

Terminator:
    T_NEWLINE
  ;

%%


void
Gambit::Parser::error(const location_type& l, const std::string& m )
{
  std::cout << m << std::endl;
}
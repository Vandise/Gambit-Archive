%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Gambit}
%define parser_class_name {Parser}

%code requires {

  #include <vector>
  #include <string>
  #include <iostream>
  #include "dev/debugnew/debug_new.h"

  namespace Gambit {
    class Scanner;
  }

  namespace Extensions {
    class iDriver;
  }

  namespace AST {
    class Node;
    class Tree;
  }

  namespace Gambit {
    class Tree;
    class LiteralNode;
  }

}

%parse-param { Gambit::Scanner &scanner }
%parse-param { AST::Tree  &astTree  }

%code {

  #include "gambit/lang/driver.hpp"
  #include "gambit/scanner.hpp"

  #undef yylex
  #define yylex scanner.yylex

  using namespace std;
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
  AST::Tree *tree;
  AST::Node *node;
}

%type <tree>    Expressions
%type <node>    Expression Literals

%%

root:
  END
  | Expressions END                     { astTree.pushBranch($1); }
  ;

Expressions:
  Expression                          {
                                        std::vector<AST::Node *> nodes;
                                        nodes.push_back($1);
                                        $$ = new Gambit::Tree(nodes);
                                      }
  | Expressions Terminator Expression {
                                        $1->pushNode($3);
                                        $$ = $1;
                                      }

  | Expressions Terminator            { $$ = $1; }
  ;

Expression:
    Literals
  ;

Literals:
  T_INTEGER                           {
                                        $$ = new Gambit::LiteralNode($1);
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
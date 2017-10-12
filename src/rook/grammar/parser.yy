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

  namespace RookAST {
    class Node;
    class Tree;
    class RookTree;
  }

}

%parse-param { Rook::Scanner &scanner }
%parse-param { RookAST::Tree  &astTree  }

%code {

  #include "rook/ast/ast.hpp"
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
%token       <ival>      T_INTEGER
%token       <sval>      T_CONSTANT
%token                   T_PUSH_INTEGER
%token                   T_SET_LOCAL
%token                   T_MAIN_LABEL
%token                   T_NEWLINE

%union {
  int ival;
  std::string *sval;
  RookAST::Tree *tree;
  RookAST::Node *node;
}

%type <tree>    Expressions
%type <node>    Expression Instructions Labels

%%

root:
  END
  | Expressions END                     { astTree.pushBranch($1); }
  ;

Expressions:
    Expression                          {
                                          std::vector<RookAST::Node *> nodes;
                                          nodes.push_back($1);
                                          $$ = new RookAST::RookTree(nodes);
                                        }
  | Expressions Terminator Expression {
                                        $1->pushNode($3);
                                        $$ = $1;
                                      }

  | Expressions Terminator            { $$ = $1; }
  ;

Expression:
    Instructions
  | Labels
  ;

Instructions:
    T_PUSH_INTEGER T_INTEGER         { std::cout << "push integer " << $2 << std::endl; $$ = nullptr; }
  | T_SET_LOCAL T_CONSTANT T_INTEGER { std::cout << "set local " << *$2 << std::endl; delete($2); $$ = nullptr; }
  ;

Labels:
    T_MAIN_LABEL { $$ = nullptr; }
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
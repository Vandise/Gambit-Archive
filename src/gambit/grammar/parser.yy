%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Gambit}
%define parser_class_name {Parser}
%define parse.error verbose

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
    class LocalDefinitionNode;
  }

}

%parse-param { Gambit::Scanner &scanner }
%parse-param { AST::Tree  &astTree  }

%code {

  #include "gambit/lang/driver.hpp"
  #include "gambit/scanner.hpp"
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
%type <node>    Expression Literals LocalDefinition

%destructor { delete($$); } <tree> <sval>

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
  | LocalDefinition
  ;

Literals:
  T_INTEGER                           {
                                        $$ = new Gambit::LiteralNode($1, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN)));
                                      }
  ;

LocalDefinition:
    T_CONSTANT T_BIND T_IDENTIFIER    {
                                        $$ = new Gambit::LocalDefinitionNode(*$1, *$3, nullptr, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN)));
                                        delete($1);
                                        delete($3);
                                      }

  | T_CONSTANT T_BIND T_IDENTIFIER T_ASSIGN Expression   
                                      {
                                        $$ = new Gambit::LocalDefinitionNode(*$1, *$3, $5, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN)));
                                        delete($1);
                                        delete($3);
                                      }
  ;

Terminator:
    T_NEWLINE
  ;

%%


void
Gambit::Parser::error(const location_type& l, const std::string& m )
{
  throw Exception::UnexpectedToken(m, SOURCE_FILE, l.begin.line, l.end.column);
}
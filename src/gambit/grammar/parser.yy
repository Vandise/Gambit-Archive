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
    class CallNode;
    class Arguments;
    class Parameters;
  }

}

%parse-param { Gambit::Scanner &scanner }
%parse-param { AST::Tree  &astTree  }

%code {

  #include <vector>

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
%token                   T_OPEN_PAREN
%token                   T_CLOSE_PAREN
%token                   T_COMMA
%token                   T_SKINNY_ARROW
%token                   T_OPEN_BRACE
%token                   T_CLOSE_BRACE
%token                   T_DEFINE
%token                   T_FAT_ARROW
%token                   T_NEWLINE

%union {
  int ival;
  int NOOP;
  std::string *sval;
  AST::Tree *tree;
  AST::Node *node;
  Gambit::Arguments *arguments;
  Gambit::Parameters *params;
}

%type <tree>      Expressions
%type <node>      Expression Literals LocalDefinition Call Locals MethodDefinition Returns
%type <arguments> Arguments
%type <params>    ParameterDefinition
%type <NOOP>      Terminator

/*
%destructor { delete($$); } <tree> <sval>
*/

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
  | Call
  | Locals
  | MethodDefinition
  | Returns
  ;

Literals:
  T_INTEGER                           {
                                        $$ = new Gambit::LiteralNode($1, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN)));
                                      }
  | T_STRING                          {
                                        $$ = new Gambit::LiteralNode(*$1, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN))); delete($1);
                                      }
  ;

LocalDefinition:
  T_CONSTANT T_BIND T_IDENTIFIER T_ASSIGN Expression   
                                      {
                                        $$ = new Gambit::LocalDefinitionNode(*$1, *$3, $5, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN)));
                                        delete($1);
                                        delete($3);
                                      }
  ;

Call:
    T_IDENTIFIER T_OPEN_PAREN Arguments T_CLOSE_PAREN { 
                                                        $$ = new Gambit::CallNode(*$1, $3, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN)));
                                                        delete($1);
                                                      }
  ;

Locals:
    T_IDENTIFIER                      { $$ = new Gambit::GetLocalNode(*$1, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN))); delete($1); }
  ;

MethodDefinition:

    T_DEFINE T_IDENTIFIER T_SKINNY_ARROW ParameterDefinition T_SKINNY_ARROW T_CONSTANT Terminator
    T_OPEN_BRACE Terminator 
      Expressions
    T_CLOSE_BRACE            { $$ = new Gambit::MethodDefinitionNode(*$2, $4, *$6, $10, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN))); delete($2); delete($6); }

  | T_DEFINE T_IDENTIFIER T_SKINNY_ARROW T_CONSTANT Terminator
    T_OPEN_BRACE Terminator 
      Expressions
    T_CLOSE_BRACE            { $$ = new Gambit::MethodDefinitionNode(*$2, nullptr, *$4, $8, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN))); delete($2); delete($4); }

  ;

ParameterDefinition:
    T_CONSTANT T_BIND T_IDENTIFIER                                    { $$ = new Gambit::Parameters(); $$->add(*$3, *$1); delete($3); delete($1); }
  | ParameterDefinition T_SKINNY_ARROW T_CONSTANT T_BIND T_IDENTIFIER { $$->add(*$5, *$3); delete($3); delete($5); }
  ;

Arguments:
    Expression {
                  $$ = new Gambit::Arguments();
                  $$->add($1);
               }
  | Arguments T_COMMA Expression { $1->add($3); $$ = $1; }
  |            { $$ = new Gambit::Arguments();  }
  ;

Returns:
    T_FAT_ARROW Expression { $$ = new Gambit::ReturnNode($2, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN))); }
  | T_FAT_ARROW            { $$ = new Gambit::ReturnNode(nullptr, (new AST::SourceTrace(SOURCE_FILE, SOURCE_LINE, SOURCE_COLUMN))); }
  ;

Terminator:
    T_NEWLINE { $$ = 0; }
  ;

%%


void
Gambit::Parser::error(const location_type& l, const std::string& m )
{
  throw Exception::UnexpectedToken(m, SOURCE_FILE, l.begin.line, l.end.column);
}
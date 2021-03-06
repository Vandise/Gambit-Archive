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
%token                   T_PUSH_STRING
%token                   T_SET_LOCAL
%token                   T_GET_LOCAL
%token                   T_PUSH_SELF
%token                   T_CALL
%token                   T_BY_VALUE
%token                   T_RETURN
%token       <sval>      T_METHOD_SIGNATURE
%token       <sval>      T_ADD_LITERAL
%token       <sval>      T_LABEL
%token                   T_NEWLINE

%union {
  int ival;
  bool bVal;
  std::string *sval;
  RookAST::Tree *tree;
  RookAST::Node *node;
}

%type <tree>    Expressions
%type <node>    Expression Instructions Labels Literals
%type <bVal>    ReferenceTypes

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
  | Literals
  ;

Instructions:
    T_PUSH_INTEGER T_INTEGER              { $$ = new RookAST::PushIntegerNode($2); }
  | T_PUSH_STRING T_INTEGER               { $$ = new RookAST::PushStringNode($2); }
  | T_SET_LOCAL T_CONSTANT T_INTEGER      { $$ = new RookAST::SetLocalNode(*$2, $3); delete($2); }
  | T_GET_LOCAL ReferenceTypes T_INTEGER  { $$ = new RookAST::GetLocalNode($3, $2); }
  | T_PUSH_SELF                           { $$ = new RookAST::PushSelfNode(); }
  | T_CALL T_METHOD_SIGNATURE T_INTEGER   { $$ = new RookAST::CallNode(*$2, $3); delete($2); }
  | T_RETURN T_INTEGER                    { $$ = new RookAST::ReturnNode($2); }
  ;

ReferenceTypes:
    T_BY_VALUE                      { $$ = true; }
  |                                 { $$ = false; }
  ;

Labels:
    T_LABEL { $$ = new RookAST::LabelNode(*$1); delete($1); }
  ;

Literals:
    T_ADD_LITERAL { $$ = new RookAST::AddLiteralNode(*$1); delete($1); }
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
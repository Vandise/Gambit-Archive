%x  incl
%{

#include <iostream>
#include <fstream>
#include <string>
#include "gambit/scanner.hpp"
#include "dev/debugnew/debug_new.h"

#undef  YY_DECL
#define YY_DECL int Gambit::Scanner::yylex( Gambit::Parser::semantic_type * const lval, Gambit::Parser::location_type *loc ) 

using token = Gambit::Parser::token;

#define YY_NO_UNISTD_H
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="Gambit::Scanner"
%option noyywrap
%option c++
%option yylineno

digit ([0-9])
integer ({digit}+)
float_num ({digit}+\.{digit}+)

%%

%{
  yylval = lval;
%}

[ \t]*              /* skip whitespace */
\n                  {
                      loc->lines();
                      return( token::T_NEWLINE );
                    }
([A-Z][a-zA-Z]*)+   {
                      yylval->sval = new std::string(yytext);
                      return( token::T_CONSTANT );
                    }
[_a-zA-Z\\?\\!]+    {
                      yylval->sval = new std::string(yytext);
                      return( token::T_IDENTIFIER ); 
                    }
\"[^"]*\"           {
                      yylval->sval = new std::string(yytext);
                      yylval->sval->erase(remove(yylval->sval->begin(), yylval->sval->end(), '\"' ), yylval->sval->end());
                      return( token::T_STRING );
                    }
{integer}           {
                      yylval->ival = (atoi(yytext));
                      return( token::T_INTEGER );
                    }
"("                 { return( token::T_OPEN_PAREN ); }
")"                 { return( token::T_CLOSE_PAREN ); }
"="                 {
                      return( token::T_ASSIGN );
                    }
"["                 {
                      return( token::T_OPEN_BRACKET );
                    }
"]"                 {
                      return( token::T_CLOSE_BRACKET );
                    }
","                 {
                      return( token::T_COMMA );
                    }
"::"                {
                      return( token::T_BIND );
                    }
"=>"                { return( token::T_FAT_ARROW ); }
"->"                {
                      return( token::T_SKINNY_ARROW );
                    }
"{"                 {
                      return( token::T_OPEN_BRACE );
                    }
"}"                 {
                      return( token::T_CLOSE_BRACE );
                    }
"@"                 {
                      return( token::T_DEFINE );
                    }
%%
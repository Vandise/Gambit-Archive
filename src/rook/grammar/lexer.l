%x  incl
%{

#include <iostream>
#include <fstream>
#include <string>
#include "rook/scanner.hpp"
#include "dev/debugnew/debug_new.h"

#undef  YY_DECL
#define YY_DECL int Rook::Scanner::yylex( Rook::Parser::semantic_type * const lval, Rook::Parser::location_type *loc ) 

using token = Rook::Parser::token;

#define YY_NO_UNISTD_H
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="Rook::Scanner"
%option noyywrap
%option c++
%option yylineno

%x literals code

digit ([0-9])
integer ({digit}+)
float_num ({digit}+\.{digit}+)

%%

%{
  yylval = lval;
%}

<*>[ \t]*          /* skip whitespace */
<*>\n              {
                      loc->lines();
                      return( token::T_NEWLINE );
                    }

<*>.literals  		 		 { BEGIN(literals); return( token::T_MAIN_LABEL );  }
<*>.code  		 		     { BEGIN(code); return( token::T_MAIN_LABEL ); }

<literals>[_a-zA-Z\\?\\!]+   { yylval->sval = new std::string(yytext); return( token::T_ADD_LITERAL ); }
<literals>\"[^"]*\"          {
                                yylval->sval = new std::string(yytext);
                                yylval->sval->erase(remove(yylval->sval->begin(), yylval->sval->end(), '\"' ), yylval->sval->end());
                                return( token::T_ADD_LITERAL );
                             }

<code>SET_LOCAL              { return( token::T_SET_LOCAL ); }
<code>PUSH_INTEGER           { return( token::T_PUSH_INTEGER ); }
<code>PUSH_STRING            { return( token::T_PUSH_STRING ); }
<code>([A-Z][a-zA-Z]*)+      {
                               yylval->sval = new std::string(yytext);
                               return( token::T_CONSTANT );
                             }
<code>{integer}  			       {
                                yylval->ival = (atoi(yytext));
                                return( token::T_INTEGER );
                             }


<*>. { std::cout << "Unexpected token " << yytext << std::endl; }

%%
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

<INITIAL>.literals  		 {
								std::cout << "switching to lierals" << std::endl;
								BEGIN(literals);
							 }

<literals>[_a-zA-Z\\?\\!]+   { std::cout << "Adding Literal: " << yytext << std::endl; }


<*>. { std::cout << "Unexpected token " << yytext << std::endl; }

%%
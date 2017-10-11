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

<*>.literals  		 		 {
								std::cout << "switching to literals" << std::endl;
								BEGIN(literals);
							 }
<*>.code  		 		     {
								std::cout << "switching to code" << std::endl;
								BEGIN(code);
							 }

<literals>[_a-zA-Z\\?\\!]+   { std::cout << "Adding Literal: " << yytext << std::endl; }

<code>SET_LOCAL              { std::cout << "setting local" << std::endl; }
<code>PUSH_INTEGER           { std::cout << "pushing integer instr" << std::endl;    }
<code>([A-Z][a-zA-Z]*)+      { std::cout << "Found classname " << yytext << std::endl; }
<code>{integer}  			 { std::cout << "Found integer " << yytext << std::endl; }


<*>. { std::cout << "Unexpected token " << yytext << std::endl; }

%%
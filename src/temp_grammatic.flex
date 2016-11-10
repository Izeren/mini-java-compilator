%{
#include <iostream>
#include "bison.hpp"

extern YYLTYPE yyloc;
int line_number = 0;
int column_number = 0;

static void updateLocation() {
    // Начало токена
    yylloc.first_line = line_number;
    yylloc.first_column = column_number;

    // Новое смещение
    for (int i = 0; i < yyleng; i++) {
      if( yytext[i] == '\n' ) {
        line_number++;
        column_number = 1;
      } else {
        column_number++;
      }
    }
    // Конец токена
    yylloc.last_line = line_number;
    yylloc.last_column = column_number;

    printf( "%s", yytext );
}

void print_debug(const char *text) {
	//std::cout << text;
}

#define YY_USER_ACTION updateLocation();
%}

DIGIT [0-9]
LETTER [a-zA-Z_]
ID [a-zA-Z][_a-zA-Z0-9]*
IntegerLiteral [1-9]{DIGIT}*|0

%option noyywrap

%%
"/*"((("*"[^/])?)|[^*])*"*/" { 
	print_debug("COMMENT");
	//return COMMENT;
}
"class" {
	return CLASS;
}
"extends" {
	return EXTENDS; 
}
"public" { 
	return PUBLIC;
}
"private" {
	return PRIVATE;
}
"this" { 
	return THIS;
}
"new" { 
	return NEW;
}
"return" { 
	return RETURN;
}
"main" {
	return MAIN;
}
"static" {
	return STATIC;
}

"System.out.println" { 
	return PRINTLN;
}
"int[]" {
	return INT_ARRAY;
}
"int" { 
	return INT;
}
"void" {
	return VOID;
}
"String" {
	return STRING;
}
{IntegerLiteral} { 
	return NUM;
}

"if" { 
	return IF;
}
"else" { 
	return ELSE;
}
"while" { 
	return WHILE; 
}

"length" {
	return LENGTH;
}

"boolean" { 
	return BOOLEAN;
}
"true" { 
	return TRUE;
}
"false" { 
	return FALSE;
}
"<" {
	return LESS;
}
">" {
	return GREATER;
}
"!" {
	return NOT;
}
"=" {
	return ASSIGN;
}
"&&" { 
	return AND;
}
"||" { 
	return OR;
}

"+" { 
	return PLUS;
}
"-" { 
	return MINUS;
}
"*" { 
	return TIMES;
}

"(" { 
	return LPAREN;
}
")" { 
	return RPAREN;
}
"[" { 
	return LBRACKET;
}
"]" { 
	return RBRACKET;
}
"{" { 
	print_debug("{");
	return LBRACE;
}
"}" { 
	print_debug("}");
	return RBRACE;
}
"," { 
	return COMMA;
}
"." { 
	return DOT; 
}
";" { 
	return SEMI; 
}
"%" {
	return MOD;
}
{ID} { 
	yylval.string = yytext;
	return ID;
}
" " {}

"\t" {}

"\n" {}

. {
	std::cerr<<"ERROR IN FLEX:"<<yytext[0]<<std::endl;
  }
%%

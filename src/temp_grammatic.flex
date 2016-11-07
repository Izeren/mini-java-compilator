%{
#include <iostream>
#include "bison.hpp"

struct {
	int first_line;
	int last_line;
	int first_column;
	int last_column;
} yylloc;
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

#define YY_USER_ACTION updateLocation();
%}

DIGIT [0-9]
LETTER [a-zA-Z_]
ID [a-zA-Z][_a-zA-Z0-9]*
IntegerLiteral [1-9]{DIGIT}*|0

%option noyywrap

%%
"class" {
	return CLASS;
}
"extends" {
	return EXTENDS; 
}
"public" { 
	return PUBLIC;
}
"protected" {
	return PROTECTED;
}
"private" {
	return PRIVATE;
}
"System.out.println" { 
	return PRINTLN;
}
"System.out.print" { 
	return PRINT;
}
"int" { 
	return INT;
}
"boolean" { 
	return BOOLEAN;
}
"if" { 
	return IF;
}
"else" { 
	return ELSE;
}
{IntegerLiteral} { 
	return NUM;
}
"while" { 
	return WHILE; 
}
"true" { 
	return TRUE;
}
"false" { 
	return FALSE;
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
"void" {
	return VOID;
}
"String" {
	return STRING;
}
{ID} { 
	return ID;
}
"<" {
	return LESS;
}
">" {
	return GREATER;
}
"=" {
	return ASSIGN;
}
"==" {
	return EQUALS;
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
	return LBRACE;
}
"}" { 
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
"/*"((("*"[^/])?)|[^*])*"*/" { 
	return COMMENT;
}
. { ; }
%%

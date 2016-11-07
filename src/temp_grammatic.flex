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
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return CLASS;
}
"extends" {
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return EXTENDS; 
}
"public" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return PUBLIC;
}
"System.out.println" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return PRINTLN;
}
"System.out.print" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return PRINT;
}
"int" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return INT;
}
"boolean" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return BOOLEAN;
}
"if" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return IF;
}
"else" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return ELSE;
}
{IntegerLiteral} { 
	//std::cout << "(" << yytext << "){" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return NUM;
}
"while" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return WHILE; 
}
"true" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return TRUE;
}
"false" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return FALSE;
}
"this" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return THIS;
}
"new" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return NEW;
}
"return" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
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
	//std::cout << "(" << yytext << "){" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return ID;
}
"<" {
	return LESS;
}
">" {
	return GREATER;
}
"=" {
	return EQUALS;
}
"&&" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return AND;
}
"||" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return OR;
}
"+" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return PLUS;
}
"-" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return MINUS;
}
"*" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return TIMES;
}
"(" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return LPAREN;
}
")" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return RPAREN;
}
"[" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return LBRACKET;
}
"]" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return RBRACKET;
}
"{" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return LBRACE;
}
"}" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
	return RBRACE;
}
"," { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return COMMA;
}
"." { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return DOT; 
}
";" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return SEMI; 
}
"/*"((("*"[^/])?)|[^*])*"*/" { 
	//std::cout << "{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
	return COMMENT;
}
. { ; }
%%

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
	std::cout << "T_CLass{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
}
"extends" {
	std::cout << "T_Extends{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
}
"public" { 
	std::cout << "T_Public{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
}
"System.out.println" { 
	std::cout << "PRINTLN{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
}
"System.out.print" { 
	std::cout << "PRINT{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
}
"int" { 
	std::cout << "T_Int{" << yylloc.first_line << ":" << yylloc.first_column << "} "; 
}
"boolean" { 
	std::cout << "BOOLEAN{" << yylloc.first_line << ":" << yylloc.first_column << "} ";
}
"if" { std::cout << "IF{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"else" { std::cout << "ELSE{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
{IntegerLiteral} { std::cout << "NUM(" << yytext << "){" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"while" { std::cout << "WHILE{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"true" { std::cout << "TRUE{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"false" { std::cout << "FALSE{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"this" { std::cout << "THIS{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"new" { std::cout << "NEW{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"return" { std::cout << "RETURN{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
{ID} { std::cout << "id(" << yytext << "){" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"&&"|"+"|"-"|"*" { std::cout << "BinaryOp{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"(" { std::cout << "LPAREN{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
")" { std::cout << "RPAREN{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"[" { std::cout << "LBRACKET{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"]" { std::cout << "RBRACKET{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"{" { std::cout << "LBRACE{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"}" { std::cout << "RBRACE{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"," { std::cout << "COMMA{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"." { std::cout << "DOT{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"; }" { std::cout << "SEMI{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
"/*"((("*"[^/])?)|[^*])*"*/" { std::cout << "COMMENT{" << yylloc.first_line << ":" << yylloc.first_column << "} "; }
. { ; }
%%

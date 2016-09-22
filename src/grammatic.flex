%{
#include <iostream>
#include "grammatic.tab.c"


extern int yylex();
static void updateLocation() {
    // Начало токена
    yylloc.first_line = 0;
    // yylloc.first_line = line_number;
    // yylloc.first_column = column_number;

    // Новое смещение
    for (int i = 0; i < yyleng; i++) {
      if( yytext[i] == '\n' ) {
        // line_number++;
        // column_number = 1;
      } else {
        // column_number++;
      }
    }
    // Конец токена
    // yylloc.last_line = line_number;
    // yylloc.last_column = column_number;

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
"class" { std::cout << "T_Class "; }
"extends" { std::cout << "T_Extends "; }
"public" { std::cout << "T_Public "; }
"System.out.println" { std::cout << "PRINT "; }
"System.out.print" { std::cout << " "; }
"int" { std::cout << "T_Int "; }
"boolean" { std::cout << "BOOLEAN "; }
"if" { std::cout << "IF "; }
"else" { std::cout << "ELSE "; }
{IntegerLiteral} { std::cout << "NUM(" << yytext << ") "; }
"while" { std::cout << "WHILE "; }
"true" { std::cout << "TRUE "; }
"false" { std::cout << "FALSE "; }
"this" { std::cout << "THIS "; }
"new" { std::cout << "NEW "; }
"return" { std::cout << "RETURN "; }
{ID} { std::cout << "id(" << yytext << ") "; }
"&&"|"+"|"-"|"*" { std::cout << "BinaryOp "; }
"(" { std::cout << "LPAREN "; }
")" { std::cout << "RPAREN "; }
"[" { std::cout << "LBRACKET "; }
"]" { std::cout << "RBRACKET "; }
"{" { std::cout << "LBRACE "; }
"}" { std::cout << "RBRACE "; }
"," { std::cout << "COMMA "; }
"." { std::cout << "DOT "; }
"; }" { std::cout << "SEMI "; }
"/*"((("*"[^/])?)|[^*])*"*/" { std::cout << "COMMENT "; }
. { ; }
%%

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    yylex(0, 0);
}
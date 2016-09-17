%{
static void updateLocation()
{
    // Начало токена
    yylloc.first_line = line_number;
    yylloc.first_column = column_number;

    // Новое смещение
    for( int i = 0; i < yyleng; i++ ) {
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


%}

DIGIT			[0-9]
LETTER			[a-zA-Z_]
ID 				{LETTER}({DIGIT}|{LETTER})*
IntegerLiteral 	[1-9]{DIGIT}*|0

%%

"class" updateLocation(); std::cout << "T_Class ";
"extends" updateLocation(); std::cout << "T_Extends ";
"public" updateLocation(); std::cout << "T_Public ";
"System.out.println" updateLocation(); std::cout << "PRINT ";
"int" updateLocation(); std::cout << "T_Int ";
"boolean" updateLocation(); std::cout << "BOOLEAN ";
"if" updateLocation(); std::cout << "IF ";
"else" updateLocation(); std::cout << "ELSE ";
IntegerLiteral updateLocation(); std::cout << "NUM(" << yytext << ") ";
"while" updateLocation(); std::cout << "WHILE ";
"true" updateLocation(); std::cout << "TRUE ";
"false" updateLocation(); std::cout << "FALSE ";
"System.out.print" updateLocation(); std::cout << " ";
"this" updateLocation(); std::cout << "THIS ";
"new" updateLocation(); std::cout << "NEW ";
"(" updateLocation(); std::cout << "LPAREN ";
")" updateLocation(); std::cout << "RPAREN ";
"[" updateLocation(); std::cout << "LBRACKET ";
"]" updateLocation(); std::cout << "RBRACKET ";
"{" updateLocation(); std::cout << "LBRACE ";
"}" updateLocation(); std::cout << "RBRACE ";
ID updateLocation(); std::cout << "id(" << yytext << ") ";
"&&"|[\+\-\*<] updateLocation(); std::cout << "BINARY ";
"return" updateLocation(); std::cout << "RETURN ";
"," updateLocation(); std::cout << "COMMA ";
"." updateLocation(); std::cout << "DOT ";
";" updateLocation(); std::cout << "SEMI ";
. updateLocation();
"/*"((("*"[^/])?)|[^*])*"*/" updateLocation(); std::cout << "COMMENT "

%%
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <stdbool.h>
       
    #define YYERROR_VERBOSE 1        
    int yylex (void);
    void yyerror (char const *s) {
      fprintf (stderr, "%s\n", s);
    }
%}


%%

program
    :
    ;

// Выражение
// Exp:
//     Exp '+' Exp { $$ = new CAriphmeticExp( $1, CAriphmeticExp::O_Plus, $3 ); }
//     | Exp '-' Exp { $$ = new CAriphmeticExp( $1, CAriphmeticExp::O_Minus, $3 ); }
//     | Exp '*' Exp { $$ = new CAriphmeticExp( $1, CAriphmeticExp::O_Mult, $3 ); }
//     | Exp '/' Exp { $$ = new CAriphmeticExp( $1, CAriphmeticExp::O_Div, $3 ); }
%%
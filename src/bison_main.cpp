#include "shared_ptr_nodes/Expressions.h"
#include "shared_ptr_nodes/Statements.h"
#include "shared_ptr_nodes/Classes.h"
#include "lex.h"
#include "bison.hpp"

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    yyparse();
}
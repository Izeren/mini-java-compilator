#include "shared_ptrs_nodes/Expressions.h"
#include "shared_ptrs_nodes/Statements.h"
#include "shared_ptrs_nodes/Classes.h"
#include "lex.h"
#include "bison.hpp"
#include <sstream>
#include <memory>
#include "shared_ptrs_visitors/CPrintVisitor.h"
#include "shared_ptrs_visitors/CConvertVisitor.h"
#include <string>
#include <fstream>
#include <iostream>

extern int line_number, column_number;

int main( int argc, char **argv ) {

	CProgram *cProgram;
	if( argc == 0 ) {
		yyin = stdin;
		yyparse(&cProgram);
    	std::unique_ptr<CProgram> program = std::unique_ptr<CProgram>(cProgram);

	} else {
		std::stringstream buffer;
		for( size_t i = 1; i < argc; i++ ) {
			line_number = 1;
			column_number = 1;
			buffer << argv[i];
			std::cout << std::endl << "Processing: " << buffer.str() << std::endl;
			yyin = fopen( buffer.str().c_str(), "r" );
			buffer << "-out.txt";
			yyrestart( yyin );
			yyparse(&cProgram);
			fclose( yyin );
			buffer.str( "" );
			std::unique_ptr<CProgram> program = std::unique_ptr<CProgram>(cProgram);
			CPrintVisitor visitor = CPrintVisitor();
			program->Accept(visitor);
			std::string result = visitor.GetResult();
			std::ofstream out(std::to_string(i) + "_digraph.txt", std::fstream::out);
			out << result;
			out.close();
		}
	}
	return 0;
}


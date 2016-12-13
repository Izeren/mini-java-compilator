#include "shared_ptrs_nodes/Expressions.h"
#include "shared_ptrs_nodes/Statements.h"
#include "shared_ptrs_nodes/Classes.h"
#include "symbol_table/SymbolInfo.h"
#include "lex.h"
#include "bison.hpp"
#include <sstream>
#include <memory>
#include "shared_ptrs_visitors/CPrintVisitor.h"
#include "shared_ptrs_visitors/CConvertVisitor.h"
#include "symbol_table/CConstructSymbolTableVisitor.h"
#include "type_checker/CTypeCheckerVisitor.h"
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
			std::cout << "Point 1\n";
			line_number = 1;
			column_number = 1;
			std::cout << "Point 2\n";
			buffer << argv[i];
			std::cout << std::endl << "Processing: " << buffer.str() << std::endl;
			yyin = fopen( buffer.str().c_str(), "r" );
			buffer << "-out.txt";
			std::cout << "Point 3\n";
			yyrestart( yyin );
			std::cout << "Point 4\n";
			std::cout << cProgram << "\n";
			yyparse(&cProgram);
			std::cout << cProgram << "\n";
			std::cout << "Point 5\n";
			fclose( yyin );
			std::cout << "Point 6\n";

			buffer.str( "" );
			std::cout << "Point 7\n";
			std::unique_ptr<CProgram> program = std::unique_ptr<CProgram>(cProgram);
			std::cout << "Point 8\n";
			CConstructSymbolTableVisitor symbol_table_visitor = CConstructSymbolTableVisitor();
			std::cout << "Point 9\n";
			std::cout << program.get() << "\n";
            std::cout << "Point 10\n";
			program->Accept(symbol_table_visitor);
			std::cout << "Point 11\n";
            CTypeCheckerVisitor type_checker_visitor = CTypeCheckerVisitor(symbol_table_visitor.GetSymbolTable());
			std::cout << "Point 12\n";
			program->Accept(type_checker_visitor);
			std::cout << "Point 13\n";
			std::ofstream out(std::to_string(i) + "res.java", std::fstream::out);
            symbol_table_visitor.GetSymbolTable()->Print(out);
            std::vector<CError> symbol_table_errors = symbol_table_visitor.GetErrors();
            for (auto error: symbol_table_errors) {
                out << error.GetPosition().GetStringPosition() << " " << error.GetMessage() << "\n";
            }
			std::cout << "Point 14\n";
            std::vector<CError> type_checker_errors = type_checker_visitor.GetErrors();
            for (auto error: type_checker_errors) {
                out << error.GetPosition().GetStringPosition() << " " << error.GetMessage() << "\n";
            }
			std::cout << "Point 15\n";
//			out << result;
			out.close();
		}
	}
	return 0;
}


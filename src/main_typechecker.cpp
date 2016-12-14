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
//#include "windows.h"

#include "dirent.h"

extern int line_number, column_number;

void make_test(std::string testfile_name, std::string result_name) {
    CProgram *cProgram;
    std::stringstream buffer;
    std::cout << "Point 1\n";
    line_number = 1;
    column_number = 1;
    std::cout << "Point 2\n";
    buffer << testfile_name;
    std::cout << std::endl << "Processing: " << buffer.str() << std::endl;
    yyin = fopen( testfile_name.c_str(), "r" );
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
    std::ofstream out(result_name, std::fstream::out);
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
    out.close();
} 

int main( int argc, char **argv ) {

    std::cout << "argc = "<< argc << "\n";
	if( argc == 1 ) {
        std::string tests_dir = "../tests/type_checker/";
        std::string testfiles_dir = "testfiles/";
        std::string results_dir = "results/";
        
        
        DIR *dir;
        struct dirent *entry;
        dir = opendir((tests_dir + testfiles_dir).c_str());
        if (!dir) {
            std::cout << "Error opening directory\n";
        };

        while ( (entry = readdir(dir)) != NULL) {
            std::string filename = entry->d_name;
            std::string java_extension = ".java";
            if (filename.rfind(java_extension) == filename.length() - java_extension.length()) {
                make_test(tests_dir + testfiles_dir + filename, tests_dir + results_dir + filename);
            }
        };

        closedir(dir);

	} else {
		for( size_t i = 1; i < argc; i++ ) {
            std::string filename = argv[i];
            make_test(filename, std::to_string(i) + "res.java");
		}
	}
	return 0;
}


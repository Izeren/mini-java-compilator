//
// Created by izeren on 3/27/17.
//

#include "IRT/nodes/Expressions.h"
#include "IRT/nodes/Statements.h"
#include "IRT/visitors/CBuildVisitor.h"
#include "IRT/visitors/PrintVisitor.h"
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

void make_test( std::string testfile_name, std::string result_name ) {
    std::cout << "in make_test, testfile_name: " << testfile_name << " result_name: " << result_name << "\n";
    CProgram *cProgram;
    std::stringstream buffer;
    line_number = 1;
    column_number = 1;
    buffer << testfile_name;
    std::cout << std::endl << "Processing: " << buffer.str( ) << std::endl;
    yyin = fopen( testfile_name.c_str( ), "r" );
    buffer << "-out.txt";
    yyrestart( yyin );
//    std::cout << cProgram << "\n";
    yyparse( &cProgram );
//    std::cout << cProgram << "\n";
    fclose( yyin );

    buffer.str( "" );
    std::unique_ptr<CProgram> program = std::unique_ptr<CProgram>( cProgram );
    CConstructSymbolTableVisitor symbol_table_visitor = CConstructSymbolTableVisitor( );
//    std::cout << program.get( ) << "\n";
    program->Accept( symbol_table_visitor );
    CTypeCheckerVisitor type_checker_visitor = CTypeCheckerVisitor( symbol_table_visitor.GetSymbolTable( ));
    program->Accept( type_checker_visitor );
    std::ofstream out( result_name, std::fstream::out );
//    symbol_table_visitor.GetSymbolTable( )->Print( out );
    std::vector<CError> symbol_table_errors = symbol_table_visitor.GetErrors( );
    std::vector<CError> type_checker_errors = type_checker_visitor.GetErrors( );
    std::cout << "total number of errors: " << symbol_table_errors.size( ) + type_checker_errors.size( ) << "\n";
    if ( symbol_table_errors.size( ) + type_checker_errors.size( ) == 0 ) {
        std::cout << "building IRTrees\n";
        CBuildVisitor iRTVisitor = CBuildVisitor( symbol_table_visitor.GetSymbolTable( ).get( ));
        program->Accept( iRTVisitor );
        std::shared_ptr<const MethodToIRTMap> trees = iRTVisitor.GetMethodFromIrtMap();
        for ( auto it = trees->begin(); it != trees->end(); ++it) {
            out << "parsed tree\n";
        }
    }
// else {
//        for ( auto error: symbol_table_errors ) {
//            out << error.GetPosition( ).GetStringPosition( ) << " " << error.GetMessage( ) << "\n";
//        }
//        for ( auto error: type_checker_errors ) {
//            out << error.GetPosition( ).GetStringPosition( ) << " " << error.GetMessage( ) << "\n";
//        }
//    }
    out.close( );
}

int main( int argc, char **argv ) {

    std::cout << "argc = " << argc << "\n";
    if ( argc == 1 ) {
        std::string tests_dir = "../tests/IRT_builder/";
        std::string testfiles_dir = "testfiles/";
        std::string results_dir = "results/";


        DIR *dir;
        struct dirent *entry;
        dir = opendir(( tests_dir + testfiles_dir ).c_str( ));
        if ( !dir ) {
            std::cout << "Error opening directory\n";
        };

        while (( entry = readdir( dir )) != NULL ) {
            std::string filename = entry->d_name;
            std::string java_extension = ".java";
            if ( filename.rfind( java_extension ) == filename.length( ) - java_extension.length( )) {
                make_test( tests_dir + testfiles_dir + filename, tests_dir + results_dir + filename );
            }
        };

        closedir( dir );

    } else {
        for ( size_t i = 1; i < argc; i++ ) {
            std::string filename = argv[ i ];
            make_test( filename, std::to_string( i ) + "res.java" );
        }
    }
    return 0;
}


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

CProgram* parseCodeWithLex(const std::string& testfile_name) {
    CProgram *cProgram;
    line_number = 1;
    column_number = 1;
    std::cout << std::endl << "Processing: " << testfile_name << std::endl;
    yyin = fopen( testfile_name.c_str( ), "r" );
    yyrestart( yyin );
    yyparse( &cProgram );
    fclose( yyin );

    return cProgram;
}

struct SymbolTableRes {
    std::shared_ptr<SymbolTable> symbolTable;
    std::vector<CError> errors;
};

SymbolTableRes constructSymbolTable(CProgram* program) {
    CConstructSymbolTableVisitor symbol_table_visitor = CConstructSymbolTableVisitor( );
    program->Accept( symbol_table_visitor );

    SymbolTableRes res;
    res.symbolTable = symbol_table_visitor.GetSymbolTable();
    res.errors = symbol_table_visitor.GetErrors();

    return res;
}

std::vector<CError> runTypeChecker(CProgram* program, std::shared_ptr<SymbolTable> symbolTable) {
    CTypeCheckerVisitor type_checker_visitor = CTypeCheckerVisitor( symbolTable );
    program->Accept( type_checker_visitor );

    return type_checker_visitor.GetErrors();
}

void writeErrors(const std::string& description, const std::vector<CError>& errors) {
    std::cout << description << "\n";

    for (auto error : errors) {
        std::cout << error.GetPosition( ).GetStringPosition( ) << " " << error.GetMessage( ) << "\n";
    }
}

void make_test( const std::string& filename, const std::string& testfile_name, const std::string& result_name ) {
    std::cout << "\n\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    std::cout << "in make_test, testfile_name: " << testfile_name << " result_name: " << result_name << "\n";

    // LEX
    std::unique_ptr<CProgram> program = std::unique_ptr<CProgram>( parseCodeWithLex(testfile_name) );

    // SYMBOL TABLE
    SymbolTableRes symbolTableRes = constructSymbolTable(program.get());
    if (symbolTableRes.errors.size() != 0) {
        writeErrors("Symbol table errors:", symbolTableRes.errors);
        return;
    }

    // TYPE CHECKER START
    std::vector<CError> typeCheckerErrors = runTypeChecker(program.get(), symbolTableRes.symbolTable);
    if (typeCheckerErrors.size() != 0) {
        writeErrors("Type checker errors:", typeCheckerErrors);
        return;
    }

    std::cout << "building IRTrees\n";
    CBuildVisitor iRTVisitor = CBuildVisitor( symbolTableRes.symbolTable.get( ));
    program->Accept( iRTVisitor );
    std::shared_ptr<const MethodToIRTMap> trees = iRTVisitor.GetMethodFromIrtMap();
    for ( auto it = trees->begin(); it != trees->end(); ++it) {
        IRT::PrintVisitor printVisitor;
        it->second->Accept(printVisitor);
        printVisitor.GetResult();

        std::ofstream out("../tests/IRT_builder/dots/" + filename + "_" + it->first + ".dot", std::fstream::out);
        out << printVisitor.GetResult();
        out.close();
    }
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
            if ( filename == "3a.java" && filename.rfind( java_extension ) == filename.length( ) - java_extension.length( )) {
                make_test( filename, tests_dir + testfiles_dir + filename, tests_dir + results_dir + filename );
            }
        };

        closedir( dir );

    }
//    else {
//        for ( size_t i = 1; i < argc; i++ ) {
//            std::string filename = argv[ i ];
//            make_test( filename, filename, std::to_string( i ) + "res.java" );
//        }
//    }
    return 0;
}
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
#include "IRT/visitors/CCallSimplifierVisitor.h"

#include "dirent.h"
#include "IRT/visitors/CEseqFloatVisitor.h"
#include "IRT/visitors/CLinearizeVisitor.h"
#include "IRT/basic_blocks/jump_canonization.h"
#include "IRT/visitors/ConstEvaluateVisitor.h"
#include "IRT/utils/PatternMatcher.h"
#include "IRT/register_allocation/RegisterAllocation.h"

extern int line_number, column_number;

CProgram *parseCodeWithLex( const std::string &testfile_name ) {
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

SymbolTableRes constructSymbolTable( CProgram *program ) {
    CConstructSymbolTableVisitor symbol_table_visitor = CConstructSymbolTableVisitor( );
    program->Accept( symbol_table_visitor );

    SymbolTableRes res;
    res.symbolTable = symbol_table_visitor.GetSymbolTable( );
    res.errors = symbol_table_visitor.GetErrors( );

    return res;
}

std::vector<CError> runTypeChecker( CProgram *program, std::shared_ptr<SymbolTable> symbolTable ) {
    CTypeCheckerVisitor type_checker_visitor = CTypeCheckerVisitor( symbolTable );
    program->Accept( type_checker_visitor );

    return type_checker_visitor.GetErrors( );
}

void writeErrors( const std::string &description, const std::vector<CError> &errors ) {
    std::cout << description << "\n";

    for ( auto error : errors ) {
        std::cout << error.GetPosition( ).GetStringPosition( ) << " " << error.GetMessage( ) << "\n";
    }
}

void
writeIRTTrees( const std::string &filename, const std::string &suffix, std::shared_ptr<const MethodToIRTMap> trees ) {
    for ( auto it = trees->begin( ); it != trees->end( ); ++it ) {
        IRT::PrintVisitor printVisitor;
        it->second->Accept( printVisitor );
        printVisitor.GetResult( );

        std::ofstream out( "../tests/IRT_builder/dots/" + filename + "_" + it->first + suffix + ".dot",
                           std::fstream::out );
        out << printVisitor.GetResult( );
        out.close( );
    }
}

std::shared_ptr<MethodToIRTMap> canonizeIRTTreesCreateESeq( std::shared_ptr<const MethodToIRTMap> trees ) {
    std::shared_ptr<MethodToIRTMap> newTrees = std::shared_ptr<MethodToIRTMap>(
            std::move( std::unique_ptr<MethodToIRTMap>( new MethodToIRTMap( ))));
    for ( auto tree = trees->begin( ); tree != trees->end( ); ++tree ) {
        IRT::CCallSimplifierVisitor callSimplifierVisitor;
        tree->second->Accept( callSimplifierVisitor );

        std::unique_ptr<const IRT::CStatement> callSimplifiedTree = std::move( callSimplifierVisitor.getResultTree( ));
        ( *newTrees )[ tree->first ] = std::move( callSimplifiedTree );
    }
    return newTrees;
}

std::shared_ptr<MethodToIRTMap> canonizeIRTTreesDeleteEseq( std::shared_ptr<const MethodToIRTMap> trees ) {
    std::shared_ptr<MethodToIRTMap> newTrees = std::shared_ptr<MethodToIRTMap>(
            std::move( std::unique_ptr<MethodToIRTMap>( new MethodToIRTMap( ))));
    for ( auto tree = trees->begin( ); tree != trees->end( ); ++tree ) {
        IRT::CEseqFloatVisitor eseqFloatVisitor;
        tree->second->Accept( eseqFloatVisitor );

        ( *newTrees )[ tree->first ] = std::move( eseqFloatVisitor.getResultTree( ));
    }

    return newTrees;
}


std::shared_ptr<MethodToIRTMap> canonizeIRTTreesLinearize( std::shared_ptr<const MethodToIRTMap> trees ) {
    std::shared_ptr<MethodToIRTMap> newTrees = std::shared_ptr<MethodToIRTMap>(
            std::move( std::unique_ptr<MethodToIRTMap>( new MethodToIRTMap( ))));
    for ( auto tree = trees->begin( ); tree != trees->end( ); ++tree ) {

        IRT::CLinearizeVisitor linearizeVisitor;
        tree->second->Accept( linearizeVisitor );

        ( *newTrees )[ tree->first ] = std::move( linearizeVisitor.getResultTree( ));
    }

    return newTrees;
}

std::shared_ptr<MethodToIRTMap> evauluateConstBinops( std::shared_ptr<const MethodToIRTMap> trees ) {
    std::shared_ptr<MethodToIRTMap> newTrees = std::shared_ptr<MethodToIRTMap>(
            std::move( std::unique_ptr<MethodToIRTMap>( new MethodToIRTMap( ))));
    for ( auto tree = trees->begin( ); tree != trees->end( ); ++tree ) {

        IRT::ConstEvaluateVisitor visitor;
        tree->second->Accept( visitor );

        ( *newTrees )[ tree->first ] = std::move( visitor.getResult( ));
    }

    return newTrees;
}

void WriteAssemblyToFile( const AssemblyCommands &commands, std::ostream &out ) {
    for ( auto command: commands ) {
        out << command->ToString( );
    }
}

std::vector<AssemblyCommands> processIRTtoASS(std::shared_ptr<const MethodToIRTMap> methodToIRTMap, std::ostream &out) {
    std::vector<AssemblyCommands> commandsBatch;
    AssemblyCode::PatternMatcher patternMatcher;
    for ( auto it = methodToIRTMap->begin(); it != methodToIRTMap->end(); ++it) {
        out << ";-----------------------------------" << it->first << "--------------------------------------\n";
        AssemblyCommands commands = patternMatcher.GenerateCode( static_cast<const IRT::CStatementList *>(it->second.get()));
        WriteAssemblyToFile(commands, out);
        commandsBatch.push_back(commands);
    }

    return commandsBatch;
}

std::vector<AssemblyCommands> processIRTtoASSWithRegAlloc(std::shared_ptr<const MethodToIRTMap> methodToIRTMap, std::ostream &out) {
    std::vector<AssemblyCommands> commandsBatch;
    AssemblyCode::PatternMatcher patternMatcher;
    AssemblyCommands commands;
    for ( auto it = methodToIRTMap->begin(); it != methodToIRTMap->end(); ++it) {
        commands.push_back(std::make_shared<AssemblyCode::CommentCommand>("-----------------------------------" + it->first + "--------------------------------------"));
        AssemblyCommands funCommands = patternMatcher.GenerateCode( static_cast<const IRT::CStatementList *>(it->second.get()));
        commands.insert(commands.end(), funCommands.begin(), funCommands.end());
    }

    AssemblyCode::RegisterInfo registerInfo;
    registerInfo.spBeginReg = IRT::CTemp("eax");
    registerInfo.espReg = IRT::CTemp("esp");
    registerInfo.registers = { "edx", "ecx", "ebx"};
    AssemblyCommands commandsWithAlloc = AssemblyCode::allocateRegisters(commands, registerInfo);

    WriteAssemblyToFile(commandsWithAlloc, out);
    commandsBatch.push_back(commandsWithAlloc);

    return commandsBatch;
}

void make_test( const std::string &filename, const std::string &testfile_name, const std::string &result_name ) {
    std::cout
            << "\n\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    std::cout << "in make_test, testfile_name: " << testfile_name << " result_name: " << result_name << "\n";

    // LEX
    std::unique_ptr<CProgram> program = std::unique_ptr<CProgram>( parseCodeWithLex( testfile_name ));

    // SYMBOL TABLE
    SymbolTableRes symbolTableRes = constructSymbolTable( program.get( ));
    if ( symbolTableRes.errors.size( ) != 0 ) {
        writeErrors( "Symbol table errors:", symbolTableRes.errors );
        return;
    }

    // TYPE CHECKER START
    std::vector<CError> typeCheckerErrors = runTypeChecker( program.get( ), symbolTableRes.symbolTable );
    if ( typeCheckerErrors.size( ) != 0 ) {
        writeErrors( "Type checker errors:", typeCheckerErrors );
        return;
    }

    // BUILD IRT
    std::cout << "building IRTrees\n";
    CBuildVisitor iRTVisitor = CBuildVisitor( symbolTableRes.symbolTable.get( ));
    program->Accept( iRTVisitor );
    std::shared_ptr<const MethodToIRTMap> irtTreesFromAST = iRTVisitor.GetMethodFromIrtMap( );
    writeIRTTrees( filename, "0_FROM_AST", irtTreesFromAST );

    // CREATE ESEQ
    std::shared_ptr<const MethodToIRTMap> canonizedTreesWithEseq = canonizeIRTTreesCreateESeq( irtTreesFromAST );
    writeIRTTrees( filename, "1_CanonozedWithEseq", canonizedTreesWithEseq );

    // REMOVE ESEQ
    std::shared_ptr<const MethodToIRTMap> canonizedTreesWithoutEseq = canonizeIRTTreesDeleteEseq(
            canonizedTreesWithEseq );
    writeIRTTrees( filename, "2_CanonozedWithoutEseq", canonizedTreesWithoutEseq );

    // LINIARIZE
    std::shared_ptr<const MethodToIRTMap> canonizedTreesLinearized = canonizeIRTTreesLinearize(
            canonizedTreesWithoutEseq );
    writeIRTTrees( filename, "3_CanonozedLinearized", canonizedTreesLinearized );

    // BASIC BLOCKS
    std::shared_ptr<const MethodToIRTMap> canonizedTreesCjump = canonizeJumps( canonizedTreesLinearized );
    writeIRTTrees( filename, "4_CanonozedCJump", canonizedTreesCjump );

    // CONST BINOP CALCS
    std::shared_ptr<const MethodToIRTMap> constBinopEvaluatedTrees = evauluateConstBinops( canonizedTreesCjump );
    writeIRTTrees( filename, "5_ConstBinopEvaluated", constBinopEvaluatedTrees );

    // ASSEMBLY GENERATION
//    std::ofstream out( "../tests/IRT_builder/asms/" + filename + "-0_infinite-registers.asm", std::fstream::out );
//    processIRTtoASS(constBinopEvaluatedTrees, out);
//    out.close();

    // ASSEMBLY GENERATION WITH ALLOC
    std::ofstream outWithAlloc( "../tests/IRT_builder/asms/" + filename + "-1_with_alloc.asm", std::fstream::out );
    processIRTtoASSWithRegAlloc(constBinopEvaluatedTrees, outWithAlloc);
    outWithAlloc.close();
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

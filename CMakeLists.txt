cmake_minimum_required(VERSION 3.6)
project(mini_java_compilator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    src/shared_ptrs_nodes/Classes.cpp
    src/shared_ptrs_nodes/Expressions.cpp
    src/shared_ptrs_nodes/Statements.cpp
    src/shared_ptrs_visitors/CConvertVisitor.cpp
    src/shared_ptrs_visitors/CPrintVisitor.cpp
    src/symbol_table/CConstructSymbolTableVisitor.cpp
    src/symbol_table/SymbolInfo.cpp
    src/type_checker/CTypeCheckerVisitor.cpp
    src/bison.cpp
    src/lex.cpp
    src/main_typechecker.cpp
    src/symbol_table/PositionInfo.cpp)

add_executable(mini_java_compilator ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.6)
project(mini_java_compilator)

set(CMAKE_CXX_STANDARD 11)


# Create target for the parser
set(LEX_DESCRIPTION ${CMAKE_SOURCE_DIR}/src/temp_grammatic.flex)
set(BISON_DESCRIPTION ${CMAKE_SOURCE_DIR}/src/grammatic.bizon)
set(LEX_OUTPUT_H ${CMAKE_SOURCE_DIR}/src/lex.h)
set(LEX_OUTPUT_CPP ${CMAKE_SOURCE_DIR}/src/lex.cpp)
set(BISON_OUTPUT ${CMAKE_SOURCE_DIR}/src/bison.cpp)

# Create custom command for flex/lex (note the outputs)
ADD_CUSTOM_COMMAND(
        COMMAND flex --header-file=${LEX_OUTPUT_H} -o ${LEX_OUTPUT_CPP} ${LEX_DESCRIPTION}
        OUTPUT ${LEX_OUTPUT_CPP} ${LEX_OUTPUT_H})

# Create custom command for bison/yacc (note the DEPENDS)
ADD_CUSTOM_COMMAND(
        COMMAND bison -v -W -Wconflicts-rr -d -o ${BISON_OUTPUT} ${BISON_DESCRIPTION}
        OUTPUT ${BISON_OUTPUT})


#set_source_files_properties( src/bison.cpp GENERATED)
#set_source_files_properties( src/lex.h GENERATED)
#set_source_files_properties( src/lex.cpp GENERATED)

set(SOURCE_FILES
        src/shared_ptrs_nodes/Classes.cpp
        src/shared_ptrs_nodes/Expressions.cpp
        src/shared_ptrs_nodes/Statements.cpp
        src/shared_ptrs_visitors/CConvertVisitor.cpp
        src/shared_ptrs_visitors/CPrintVisitor.cpp
        src/symbol_table/CConstructSymbolTableVisitor.cpp
        src/symbol_table/SymbolInfo.cpp
        src/type_checker/CTypeCheckerVisitor.cpp
        src/IRT/utils/Frame.cpp
        #        src/main_typechecker.cpp
        src/IRT/utils/Label.cpp
        src/IRT/utils/Temporary.cpp
        src/symbol_table/PositionInfo.cpp
        src/IRT/nodes/Statements.cpp
        src/IRT/nodes/Expressions.h
        src/IRT/nodes/Expressions.cpp
        src/IRT/utils/enums.h
        src/IRT/utils/SubtreeWrapper.cpp
        src/IRT/visitors/CBuildVisitor.cpp
        src/IRT/visitors/CCallSimplifierVisitor.cpp
        src/IRT/visitors/CBuildVisitor.h
        src/IRT/utils/SubtreeWrapper.h
        src/IRT/visitors/EmptyVisitor.cpp
        src/IRT/visitors/EmptyVisitor.h
        src/IRT/visitors/PrintVisitor.cpp
        src/IRT/visitors/PrintVisitor.h
        src/IRT_builder_main.cpp src/IRT/utils/symbol_table_utils.cpp src/IRT/visitors/CLinearizeVisitor.h src/IRT/visitors/CLinearizeVisitor.cpp
        src/IRT_builder_main.cpp src/IRT/utils/symbol_table_utils.cpp src/IRT/visitors/CEseqFloatVisitor.cpp src/IRT/visitors/CEseqFloatVisitor.h
        src/IRT/basic_blocks/basic_block_divider.cpp
        src/IRT/basic_blocks/jump_canonization.cpp
        src/IRT/basic_blocks/basic_block_graph.cpp
        src/IRT/basic_blocks/basic_block_optimizer.cpp
        src/IRT/basic_blocks/basic_block_collector.cpp
        src/IRT/visitors/ConstEvaluateVisitor.cpp
        src/IRT/utils/TreePatterns.cpp
        src/IRT/utils/AssemblyCommand.cpp)


add_executable(mini_java_compilator ${SOURCE_FILES} ${LEX_OUTPUT_H} ${LEX_OUTPUT_CPP} ${BISON_OUTPUT})

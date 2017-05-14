//
// Created by izeren on 4/27/17.
//

#include "PatternMatcher.h"
#include <cassert>

void AssemblyCode::PatternMatcher::GenerateCodeForNode( const IRT::INode *node, const IRT::CTemp &dest,
                                                        AssemblyCommands &commands ) {

    AssemblyCommands nodeCommands;
    ChildrenTemps children;
    bool result = false;
    int i = 0;
    for ( auto pattern : patterns ) {
        children.clear( );
        nodeCommands.clear( );
        result = pattern->TryToGenerateCode( node, dest, children, nodeCommands );
        if ( result ) {
            break;
        }
        ++i;
    }
    assert( result );
    for ( auto child : children ) {
        GenerateCodeForNode( child.second, child.first, commands );
    }
    for ( auto command: nodeCommands ) {
        commands.push_back( command );
    }
}

AssemblyCommands AssemblyCode::PatternMatcher::GenerateCode( const IRT::CStatementList *cStatementList ) {
    AssemblyCommands commands;
    const std::vector<std::unique_ptr<const IRT::CStatement>> &statements = cStatementList->Statements( );
    IRT::CTemp fakeDest;
    for ( int index = 0; index < statements.size( ); ++index ) {
        GenerateCodeForNode( statements[ index ].get( ), fakeDest, commands );
    }
    return commands;
}

AssemblyCode::PatternMatcher::PatternMatcher( ) {
    patterns.emplace_back( std::make_shared<IRT::MoveFromMemByRegToReg>( ));
    patterns.emplace_back( std::make_shared<IRT::MemFromRegPlusConstPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::MemFromConstPlusRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::MoveFromMemByRegToMemByReg>( ));
    patterns.emplace_back( std::make_shared<IRT::MoveRegToMemByRegPlusConst>( ));
    patterns.emplace_back( std::make_shared<IRT::MoveRegToMemByConstPlusReg>( ));
    patterns.emplace_back( std::make_shared<IRT::MoveRegToMemByReg>( ));
    patterns.emplace_back( std::make_shared<IRT::MoveRegToMemByConst>( ));
    patterns.emplace_back( std::make_shared<IRT::MemFromConstPlusRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::MemFromRegPlusConstPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::MoveMemFromConstPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegPlusConstPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::ConstPlusRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::CallPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::ConditionalJumpPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::MoveRegRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegPlusRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegMinusRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegMulRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegModRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::JumpPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::ExpPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::NamePattern>( ));
    patterns.emplace_back( std::make_shared<IRT::LabelPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::ConstPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::MemPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegPattern>( ));
}
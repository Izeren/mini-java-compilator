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
    for ( auto pattern : patterns ) {
        children.clear( );
        nodeCommands.clear( );
        result = pattern->TryToGenerateCode( node, dest, children, nodeCommands );
        if ( result ) {
            break;
        }
    }
    assert( result );
    for ( auto child : children ) {
        GenerateCodeForNode( child.second, child.first, commands );
    }
    std::copy( nodeCommands.begin( ), nodeCommands.end( ), commands.end( ));
}

AssemblyCommands AssemblyCode::PatternMatcher::GenerateCode( IRT::CStatementList *cStatementList ) {
    AssemblyCommands commands;
    const std::vector<std::unique_ptr<const IRT::CStatement>> &statements = cStatementList->Statements( );
    IRT::CTemp fakeDest;
    for ( int index = 0; index < statements.size( ); ++index ) {
        GenerateCodeForNode( statements[ index ].get( ), fakeDest, commands );
    }
}

AssemblyCode::PatternMatcher::PatternMatcher( ) {
    patterns.emplace_back( std::make_shared<IRT::CallPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::MoveRegRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegPlusRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegMinusRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegMulRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegModRegPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::ExpPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::NamePattern>( ));
    patterns.emplace_back( std::make_shared<IRT::LabelPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::ConstPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::MemPattern>( ));
    patterns.emplace_back( std::make_shared<IRT::RegPattern>( ));
}

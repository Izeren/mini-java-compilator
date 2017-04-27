//
// Created by izeren on 4/27/17.
//

#pragma once

#include <vector>
#include "AssemblyCommand.h"
#include "TreePatterns.h"
#include "../nodes/Statements.h"

using AssemblyCommands = std::vector<std::shared_ptr<AssemblyCode::AssemblyCommand>>;

namespace AssemblyCode {
    class PatternMatcher {
    public:
        PatternMatcher( );

        AssemblyCommands GenerateCode( IRT::CStatementList *cStatementList );

        void GenerateCodeForNode( const IRT::INode *node, const IRT::CTemp &dest, AssemblyCommands &commands );

    private:
        std::vector<std::shared_ptr<IRT::TreePattern>> patterns;
    };
};

#pragma once

#include <memory>
#include "../utils/AssemblyCommand.h"
#include "../utils/TreePatterns.h"
#include <vector>

namespace AssemblyCode {

    struct CodeLine {
        std::shared_ptr<AssemblyCode::AssemblyCommand> command;

        int lineNumber;

        std::vector<AssemblyCode::CodeLine*> outEdges;

        std::vector<AssemblyCode::CodeLine*> inEdges;
    };

    std::vector<AssemblyCode::CodeLine> buildControlFlowGraph(const AssemblyCommands& commands);

}

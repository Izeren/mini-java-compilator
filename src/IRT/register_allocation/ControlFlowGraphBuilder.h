#pragma once

#include <memory>
#include "../utils/AssemblyCommand.h"
#include "../utils/TreePatterns.h"
#include <vector>
#include <set>

namespace AssemblyCode {

    struct CodeLine {
        std::shared_ptr<AssemblyCode::AssemblyCommand> command;

        int lineNumber;

        std::vector<AssemblyCode::CodeLine*> nextLines;

        std::vector<AssemblyCode::CodeLine*> prevLines;

        std::set<std::string> liveInTemps;

        std::set<std::string> liveOutTemps;
    };

    std::vector<AssemblyCode::CodeLine> buildControlFlowGraph(const AssemblyCommands& commands);

}

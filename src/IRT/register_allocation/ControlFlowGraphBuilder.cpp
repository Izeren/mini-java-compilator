#include "ControlFlowGraphBuilder.h"
#include <map>

std::map<std::string, int> buildLabelMap(const AssemblyCommands &commands) {
    std::map<std::string, int> map;
    for (int i = 0; i < commands.size(); ++i) {
        const AssemblyCode::LabelCommand* labelCommand =
                dynamic_cast<const AssemblyCode::LabelCommand*>(commands[i].get());

        if (labelCommand != nullptr) {
            map[labelCommand->getLabel()] = i;
        }
    }

    return map;
};

std::vector<AssemblyCode::CodeLine> AssemblyCode::buildControlFlowGraph(const AssemblyCommands &commands) {
    std::map<std::string, int> labelToIndexMap = buildLabelMap(commands);
    std::vector<AssemblyCode::CodeLine> lines;

    // fill lines
    for (int i = 0; i < commands.size(); ++i) {
        CodeLine codeLine;
        codeLine.lineNumber = i;
        codeLine.command = commands[i];

        AssemblyCode::MoveRegRegCommand* moveRegRegCommand =
                dynamic_cast<AssemblyCode::MoveRegRegCommand*>(commands[i].get());

        codeLine.isMoveRegReg = moveRegRegCommand != nullptr;

        lines.push_back(codeLine);
    }

    // build graph
    for (int i = 0; i < commands.size(); ++i) {
        const AbstractJumpCommand* abstractJumpCommand = dynamic_cast<const AbstractJumpCommand*>(commands[i].get());
        if (abstractJumpCommand != nullptr) {
            CodeLine* labelJumpLine = &lines[labelToIndexMap[abstractJumpCommand->getLabel()]];

            lines[i].nextLines.push_back(labelJumpLine);
            labelJumpLine->prevLines.push_back(&lines[i]);

            const JumpCommand* jumpCommand = dynamic_cast<const JumpCommand*>(abstractJumpCommand);
            if (jumpCommand == nullptr && (i + 1) != commands.size()) {
                // conditional jump
                CodeLine* nextLine = &lines[i + 1];
                lines[i].nextLines.push_back(nextLine);
                nextLine->prevLines.push_back(&lines[i]);
            }
        } else {
            if ((i + 1) != commands.size()) {
                lines[i].nextLines.push_back(&lines[i + 1]);
                lines[i + 1].prevLines.push_back(&lines[i]);
            }
        }
    }

    return lines;
}

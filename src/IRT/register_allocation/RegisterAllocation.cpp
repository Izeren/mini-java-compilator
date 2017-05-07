#include "RegisterAllocation.h"
#include <map>
#include <set>
#include <stack>
#include <cassert>
#include "ControlFlowGraphBuilder.h"
#include "TempLivnessFiller.h"
#include "InterferentGraphBuilder.h"
#include "../utils/Frame.h"
#include "../utils/TreePatterns.h"


std::map<std::string, std::set<std::string>> buildGraph(AssemblyCommands& commands) {
    std::vector<AssemblyCode::CodeLine> controlGraph = buildControlFlowGraph(commands);
    fillCodeLineTempLivness(controlGraph);
    return buildInterferentGraph(controlGraph);
};

bool isGraphEmpty(std::map<std::string, std::set<std::string>> &graph) {
    return graph.empty();
}

void deleteVertexFromGraph(const std::string& vertex, std::map<std::string, std::set<std::string>> &graph) {
    auto edges = graph[vertex];
    for (auto edge : edges) {
        assert(graph[edge].erase(vertex) == 1);
    }

    assert(graph.erase(vertex) == 1);
}

bool checkSimplifiableVertex(std::map<std::string, std::set<std::string>> &graph, int registerNumber) {
    for (auto vertex : graph) {
        if (vertex.second.size() < registerNumber) {
            return true;
        }
    }

    return false;
}

struct StackEntry {
    std::string temp;
    bool isSpilled;

    StackEntry(const std::string &temp) : temp(temp), isSpilled(false) {}

    StackEntry(const std::string &temp, bool isSpilled) : temp(temp), isSpilled(isSpilled) {}
};

void simplify(std::map<std::string, std::set<std::string>>& graph,
              std::stack<StackEntry>& tempStack, AssemblyCode::RegisterInfo& registerInfo) {

    bool wasSuccessfully;
    do {
        wasSuccessfully = false;

        for (auto vertex : graph) {
            if (vertex.second.size() < registerInfo.registers.size()) {
                tempStack.push(StackEntry(vertex.first));
                deleteVertexFromGraph(vertex.first, graph);
                wasSuccessfully = true;
                break;
            }
        }

    } while (wasSuccessfully);
}

void spill(std::map<std::string, std::set<std::string>>& graph,
           std::stack<StackEntry>& tempStack, AssemblyCode::RegisterInfo& registerInfo, std::set<std::string>& originalTemps) {

    while (!isGraphEmpty(graph) && !checkSimplifiableVertex(graph, registerInfo.registers.size())) {
        for (auto vertex : graph) {
            if (originalTemps.find(vertex.first) != originalTemps.end()) {
                tempStack.push( StackEntry( vertex.first, true ));
                deleteVertexFromGraph( vertex.first, graph );
            }
        }
    }
}

int IN_MEMORY_COLOR = -1;

void addTempToRecoveredGraph(const std::string& temp,
        std::map<std::string, std::set<std::string>>& originalGraph,
        std::map<std::string, std::set<std::string>>& recoveredGraph) {

    assert(recoveredGraph.find(temp) == recoveredGraph.end());

    recoveredGraph[temp] = std::set<std::string>();
    for (std::string neighbour : originalGraph[temp]) {
        if (recoveredGraph.find(neighbour) != recoveredGraph.end()) {
            AssemblyCode::addNotOrientedEdge(temp, neighbour, recoveredGraph);
        }
    }
}

int getColorForTemp(const std::string& temp,
                    std::map<std::string, std::set<std::string>>& recoveredGraph,
                    std::map<std::string, int>& tempToColorMap) {

    std::set<int> colorSet;
    for (std::string neighbour : recoveredGraph[temp]) {
        assert(tempToColorMap.find(neighbour) != tempToColorMap.end());
        colorSet.insert(tempToColorMap[neighbour]);
    }

    int color = 0;
    while (colorSet.find(color) != colorSet.end()) {
        ++color;
    }

    return color;
}

void processStackEntry(
        const StackEntry& stackEntry,
        std::map<std::string, std::set<std::string>>& originalGraph,
        std::map<std::string, std::set<std::string>>& recoveredGraph,
        int registerNumber,
        std::map<std::string, int>& tempToColorMap
) {
    addTempToRecoveredGraph(stackEntry.temp, originalGraph, recoveredGraph);
    int color = getColorForTemp(stackEntry.temp, recoveredGraph, tempToColorMap);
    if (color >= registerNumber) {
        assert(stackEntry.isSpilled);
        tempToColorMap[stackEntry.temp] = IN_MEMORY_COLOR;
    } else {
        tempToColorMap[stackEntry.temp] = color;
    }
}

int totalAllocated = 0;

int countSpilled(std::map<std::string, int>& tempToColorMap) {
    int count = 0;
    for (auto entry : tempToColorMap) {
        if (entry.second == IN_MEMORY_COLOR) {
            ++count;
        }
    }

    return count;
}

void addFirstLineAllocation(AssemblyCommands& commands, AssemblyCode::RegisterInfo& registerInfo) {
    commands.insert(commands.begin(),
                    std::make_shared<AssemblyCode::MoveRegRegCommand>(registerInfo.spBeginReg,
                                                    registerInfo.espReg));

    commands.insert(commands.begin(),
                    std::make_shared<AssemblyCode::SubRegConstCommand>(IRT::CTemp(registerInfo.espReg),
                    totalAllocated * IRT::CFrame::wordSize));
}

void colorToRegistersChange(AssemblyCommands& commands,
                            std::map<std::string, int>& tempToColorMap,
                            AssemblyCode::RegisterInfo& registerInfo) {
    for (auto entry : commands) {
        entry->colorToRegisterChange(tempToColorMap, registerInfo);
    }
}

std::map<std::string, int> buildSpillToOffsetMap(std::map<std::string, int>& tempToColorMap) {
    std::vector<std::string> spilledNodes;
    for (auto entry : tempToColorMap) {
        if (entry.second == IN_MEMORY_COLOR) {
            spilledNodes.push_back(entry.first);
        }
    }

    assert(spilledNodes.size() != 0);

    std::map<std::string, int> map;
    for (int i = 0; i < spilledNodes.size(); ++i) {
        map[spilledNodes[i]] = (totalAllocated + i) * IRT::CFrame::wordSize;
    }

    return map;
};

void processSpilledTemps(AssemblyCommands& commands,
        std::map<std::string, int>& tempToColorMap,
        AssemblyCode::RegisterInfo& registerInfo) {

    AssemblyCommands newAssemblyCommands;
    std::map<std::string, int> spilledToOffset = buildSpillToOffsetMap(tempToColorMap);
    for (auto command : commands) {
        command->processMemoryTemps(command, newAssemblyCommands, spilledToOffset, registerInfo.spBeginReg);
    }

    commands.clear();
    commands.insert(commands.end(), newAssemblyCommands.begin(), newAssemblyCommands.end());
}

bool rewriteProgram(AssemblyCommands& commands,
                    std::map<std::string, int>& tempToColorMap,
                    AssemblyCode::RegisterInfo& registerInfo) {

    int newSpilledCount = countSpilled(tempToColorMap);
    if (newSpilledCount == 0) {
        addFirstLineAllocation(commands, registerInfo);
        colorToRegistersChange(commands, tempToColorMap, registerInfo);
        return true;
    } else {
        processSpilledTemps(commands, tempToColorMap, registerInfo);
        return false;
    }
}

bool select(AssemblyCommands& commands, AssemblyCode::RegisterInfo& registerInfo,
        std::map<std::string, std::set<std::string>>& originalGraph,
        std::stack<StackEntry>& tempStack) {

    std::map<std::string, std::set<std::string>> recoveredGraph;
    std::map<std::string, int> tempToColorMap;
    while (!tempStack.empty()) {
        processStackEntry(tempStack.top(),
                          originalGraph,
                          recoveredGraph,
                          registerInfo.registers.size(),
                          tempToColorMap);
        tempStack.pop();
    }

    return rewriteProgram(commands, tempToColorMap, registerInfo);
}

bool tryAllocateRegisters(AssemblyCommands& commands, AssemblyCode::RegisterInfo& registerInfo,
                          std::set<std::string>& originalTemps) {
    // build graph
    std::map<std::string, std::set<std::string>> originalGraph = buildGraph(commands);

    // simplify and spill
    std::map<std::string, std::set<std::string>> tempGraph = originalGraph;
    std::stack<StackEntry> tempStack;
    while (!isGraphEmpty(tempGraph)) {
        simplify(tempGraph, tempStack, registerInfo);
        spill(tempGraph, tempStack, registerInfo, originalTemps);
    }

    // select
    return select(commands, registerInfo, originalGraph, tempStack);
}

std::set<std::string> getOriginalTemps(AssemblyCommands& commands) {
    std::set<std::string> temps;
    for (auto command : commands) {
        for (auto temp : command->GetOut()) {
            temps.insert(temp.ToString());
        }
    }

    return temps;
}

AssemblyCommands allocateRegisters(AssemblyCommands& commands, AssemblyCode::RegisterInfo& registerInfo) {
    AssemblyCommands commandsWithRegisters = commands;
    std::set<std::string> originalTemps = getOriginalTemps(commands);
    while (!tryAllocateRegisters(commandsWithRegisters, registerInfo, originalTemps)) {
        // 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾
    }

    return commandsWithRegisters;
}

void AssemblyCode::colorToRegisterChange( IRT::CTemp& temp,
                            std::map<std::string, int> &tempToColorMap, AssemblyCode::RegisterInfo &registerInfo ) {
    auto mapEntry = tempToColorMap.find(temp.ToString());
    if (mapEntry != tempToColorMap.end()) {
        temp.setName(registerInfo.registers[mapEntry->second]);
    }
}

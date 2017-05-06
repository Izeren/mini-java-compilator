#include "RegisterAllocation.h"
#include <map>
#include <set>
#include <stack>
#include <cassert>
#include "ControlFlowGraphBuilder.h"
#include "TempLivnessFiller.h"
#include "InterferentGraphBuilder.h"

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
              std::stack<StackEntry>& tempStack, int registerNumber) {

    bool wasSuccessfully;
    do {
        wasSuccessfully = false;

        for (auto vertex : graph) {
            if (vertex.second.size() < registerNumber) {
                tempStack.push(StackEntry(vertex.first));
                deleteVertexFromGraph(vertex.first, graph);
                wasSuccessfully = true;
                break;
            }
        }

    } while (wasSuccessfully);
}

void spill(std::map<std::string, std::set<std::string>>& graph,
           std::stack<StackEntry>& tempStack, int registerNumber) {

    while (!isGraphEmpty(graph) && !checkSimplifiableVertex(graph, registerNumber)) {
        auto vertex = graph.begin();
        tempStack.push(StackEntry(vertex->first, true));
        deleteVertexFromGraph(vertex->first, graph);
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

bool rewriteProgram(AssemblyCommands& commands, std::map<std::string, int>& tempToColorMap) {

}

bool select(AssemblyCommands& commands, int registerNumber,
        std::map<std::string, std::set<std::string>>& originalGraph,
        std::stack<StackEntry>& tempStack) {

    std::map<std::string, std::set<std::string>> recoveredGraph;
    std::map<std::string, int> tempToColorMap;
    while (!tempStack.empty()) {
        processStackEntry(tempStack.top(), originalGraph, recoveredGraph, registerNumber, tempToColorMap);
        tempStack.pop();
    }

    return rewriteProgram(commands, tempToColorMap);
}

bool tryAllocateRegisters(AssemblyCommands& commands, int registerNumber) {
    // build graph
    std::map<std::string, std::set<std::string>> originalGraph = buildGraph(commands);

    // simplify and spill
    std::map<std::string, std::set<std::string>> tempGraph = originalGraph;
    std::stack<StackEntry> tempStack;
    while (!isGraphEmpty(tempGraph)) {
        simplify(tempGraph, tempStack, registerNumber);
        spill(tempGraph, tempStack, registerNumber);
    }

    // select

}

AssemblyCommands allocateRegisters(AssemblyCommands& commands, int registerNumber) {
    AssemblyCommands commandsWithRegisters = commands;
    while (!tryAllocateRegisters(commandsWithRegisters, registerNumber)) {
        // 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾
    }

    return commandsWithRegisters;
}

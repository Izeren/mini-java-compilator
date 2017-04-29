#include "InterferentGraphBuilder.h"

void addOrientedEdge(std::string from, std::string to, std::map<std::string, std::set<std::string>>& graph) {
    if (graph.find(from) == graph.end()) {
        graph[from] = std::set<std::string>();
    }

    graph[from].insert(to);
}

void addNotOrientedEdge(std::string a, std::string b, std::map<std::string, std::set<std::string>>& graph) {
    addOrientedEdge(a, b, graph);
    addOrientedEdge(b, a, graph);
}

void addEdgesFromMoveLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph) {

}

void addEdgesFromNotMoveLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph) {
    for (auto defTemp : line.command->GetOut()) {
        for (auto outTemp : line.liveOutTemps) {
            addNotOrientedEdge(defTemp.ToString(), outTemp, graph);
        }
    }
}

void processLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph) {
    if (line.isMoveRegReg) {
        addEdgesFromMoveLine(line, graph);
    } else {
        addEdgesFromNotMoveLine(line, graph);
    }
}

std::map<std::string, std::set<std::string>> buildInterferentGraph(std::vector<AssemblyCode::CodeLine>& lines) {
    std::map<std::string, std::set<std::string>> graph;

    for (auto line : lines) {
        processLine(line, graph);
    }

    return graph;
};
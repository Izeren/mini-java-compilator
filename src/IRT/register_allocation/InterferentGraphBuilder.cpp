#include "InterferentGraphBuilder.h"
#include "../utils/Frame.h"

bool isInIgnoreList(std::string& temp) {
    if (temp == IRT::CFrame::returnValueAddressName) {
        return true;
    }

    if (temp == IRT::CFrame::framePointerAddressName) {
        return true;
    }

    return false;
}

void AssemblyCode::addOrientedEdge(std::string from, std::string to, std::map<std::string, std::set<std::string>>& graph) {
    if (graph.find(from) == graph.end()) {
        graph[from] = std::set<std::string>();
    }

    graph[from].insert(to);
}

void AssemblyCode::addNotOrientedEdge(std::string a, std::string b, std::map<std::string, std::set<std::string>>& graph) {
    addOrientedEdge(a, b, graph);
    addOrientedEdge(b, a, graph);
}

void addEdgesFromMoveLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph) {
    AssemblyCode::MoveRegRegCommand* moveRegRegCommand =
            dynamic_cast<AssemblyCode::MoveRegRegCommand*>(line.command.get());

    std::string target = moveRegRegCommand->getTarget();
    std::string source = moveRegRegCommand->getSource();

    for (auto outTemp : line.liveOutTemps) {
        if (outTemp != source) {
            if (!isInIgnoreList(outTemp) && !isInIgnoreList(target)) {
                AssemblyCode::addNotOrientedEdge( target, outTemp, graph );
            }
        }
    }
}

void addEdgesFromNotMoveLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph) {
    for (auto defTemp : line.command->GetOut()) {
        for (auto outTemp : line.liveOutTemps) {
            std::string def = defTemp.ToString( );
            std::string out = outTemp;
            if (!isInIgnoreList(def) && !isInIgnoreList(out)) {
                AssemblyCode::addNotOrientedEdge( def, out, graph );
            }
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

std::map<std::string, std::set<std::string>> AssemblyCode::buildInterferentGraph(std::vector<AssemblyCode::CodeLine>& lines) {
    std::map<std::string, std::set<std::string>> graph;

    for (auto line : lines) {
        processLine(line, graph);
    }

    return graph;
};
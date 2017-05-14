#include <cassert>
#include "InterferentGraphBuilder.h"
#include "../utils/Frame.h"

#include "IgnoreList.h"

void AssemblyCode::addOrientedEdge(std::string from, std::string to, std::map<std::string, std::set<std::string>>& graph) {
    if (graph.find(from) == graph.end()) {
        graph[from] = std::set<std::string>();
    }

    graph[from].insert(to);
}

void AssemblyCode::addNotOrientedEdge(std::string a, std::string b, std::map<std::string, std::set<std::string>>& graph) {
    assert(a != b);

    addOrientedEdge(a, b, graph);
    addOrientedEdge(b, a, graph);
}

void addEdgesFromMoveLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph) {
    AssemblyCode::MoveRegRegCommand* moveRegRegCommand =
            dynamic_cast<AssemblyCode::MoveRegRegCommand*>(line.command.get());

    std::string target = moveRegRegCommand->getTarget();
    std::string source = moveRegRegCommand->getSource();

    for (auto outTemp : line.liveOutTemps) {
        if (outTemp == source) {
            continue;
        }

        if (!isInIgnoreList(outTemp) && !isInIgnoreList(target) && target != outTemp) {
            AssemblyCode::addNotOrientedEdge( target, outTemp, graph );
        }
    }
}

void addEdgesFromNotMoveLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph) {
    for (auto defTemp : line.command->GetOut()) {
        for (auto outTemp : line.liveOutTemps) {
            if (defTemp.ToString() != outTemp) {
                std::string def = defTemp.ToString( );
                std::string out = outTemp;
                if ( !isInIgnoreList( def ) && !isInIgnoreList( out )) {
                    AssemblyCode::addNotOrientedEdge( def, out, graph );
                }
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

void addVertices(std::vector<AssemblyCode::CodeLine>& lines,
        std::map<std::string, std::set<std::string>>& g) {

    for (auto line : lines) {
        for (auto temp : line.command->GetIn()) {
            std::string t = temp.ToString();
            if (!isInIgnoreList(t)) {
                g[t] = std::set<std::string>( );
            }
        }

        for (auto temp : line.command->GetOut()) {
            std::string t = temp.ToString();
            if (!isInIgnoreList(t)) {
                g[t] = std::set<std::string>( );
            }
        }
    }
}

std::map<std::string, std::set<std::string>> AssemblyCode::buildInterferentGraph(std::vector<AssemblyCode::CodeLine>& lines) {
    std::map<std::string, std::set<std::string>> graph;

    addVertices(lines, graph);

    for (auto line : lines) {
        processLine(line, graph);
    }

    return graph;
};
#include <cassert>
#include "InterferentGraphBuilder.h"
#include "../utils/Frame.h"

#include "IgnoreList.h"
#include <algorithm>

bool isInDynamicIgnoreList(std::string temp, std::vector<std::string>& ignoreList) {
    return std::find(ignoreList.begin(), ignoreList.end(), temp) != ignoreList.end();
}

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

void addEdgesFromMoveLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph,
                          std::vector<std::string>& ignoreList) {
    AssemblyCode::MoveRegRegCommand* moveRegRegCommand =
            dynamic_cast<AssemblyCode::MoveRegRegCommand*>(line.command.get());

    std::string target = moveRegRegCommand->getTarget();
    std::string source = moveRegRegCommand->getSource();

    for (auto outTemp : line.liveOutTemps) {
        if (outTemp == source) {
            continue;
        }

        if (!isInIgnoreList(outTemp) && !isInIgnoreList(target) &&
                !isInDynamicIgnoreList(outTemp, ignoreList) && !isInDynamicIgnoreList(target, ignoreList) &&
                target != outTemp) {
            AssemblyCode::addNotOrientedEdge( target, outTemp, graph );
        }
    }
}

void addEdgesFromNotMoveLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph,
                             std::vector<std::string>& ignoreList) {
    for (auto defTemp : line.command->GetOut()) {
        for (auto outTemp : line.liveOutTemps) {
            if (defTemp.ToString() != outTemp) {
                std::string def = defTemp.ToString( );
                std::string out = outTemp;
                if ( !isInIgnoreList( def ) && !isInIgnoreList( out ) && !isInDynamicIgnoreList(def, ignoreList) && !isInDynamicIgnoreList(out, ignoreList)) {
                    AssemblyCode::addNotOrientedEdge( def, out, graph );
                }
            }
        }
    }
}

void processLine(AssemblyCode::CodeLine& line, std::map<std::string, std::set<std::string>>& graph,
                 std::vector<std::string>& ignoreList) {
    if (line.isMoveRegReg) {
        addEdgesFromMoveLine(line, graph, ignoreList);
    } else {
        addEdgesFromNotMoveLine(line, graph, ignoreList);
    }
}

void addVertices(std::vector<AssemblyCode::CodeLine>& lines,
        std::map<std::string, std::set<std::string>>& g,
                 std::vector<std::string>& ignoreList) {

    for (auto line : lines) {
        for (auto temp : line.command->GetIn()) {
            std::string t = temp.ToString();
            if (!isInIgnoreList(t) && !isInDynamicIgnoreList(t, ignoreList)) {
                g[t] = std::set<std::string>( );
            }
        }

        for (auto temp : line.command->GetOut()) {
            std::string t = temp.ToString();
            if (!isInIgnoreList(t) && !isInDynamicIgnoreList(t, ignoreList)) {
                g[t] = std::set<std::string>( );
            }
        }
    }
}

std::map<std::string, std::set<std::string>> AssemblyCode::buildInterferentGraph(std::vector<AssemblyCode::CodeLine>& lines,
                                                                                 std::vector<std::string>& ignoreList) {
    std::map<std::string, std::set<std::string>> graph;

    addVertices(lines, graph, ignoreList);

    for (auto line : lines) {
        processLine(line, graph, ignoreList);
    }

    return graph;
};
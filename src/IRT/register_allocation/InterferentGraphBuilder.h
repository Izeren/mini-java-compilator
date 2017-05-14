#include <string>
#include <set>
#include <map>
#include "ControlFlowGraphBuilder.h"

namespace AssemblyCode {

    void addOrientedEdge(std::string from, std::string to, std::map<std::string, std::set<std::string>>& graph);

    void addNotOrientedEdge(std::string a, std::string b, std::map<std::string, std::set<std::string>>& graph);

    std::map<std::string, std::set<std::string>> buildInterferentGraph(std::vector<AssemblyCode::CodeLine>& lines,
                                                                       std::vector<std::string>& ignoreList);

}

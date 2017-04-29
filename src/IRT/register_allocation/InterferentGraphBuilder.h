#include <string>
#include <set>
#include <map>
#include "ControlFlowGraphBuilder.h"

namespace AssemblyCode {

    std::map<std::string, std::set<std::string>> buildInterferentGraph(std::vector<AssemblyCode::CodeLine>& lines);

}

#pragma once

#include <map>
#include <string>
#include "../nodes/Statements.h"
#include "../utils/Label.h"

namespace IRT {

    // label -> block index
    std::map<std::string, int> buildBasicBlocksGraph(
            const std::vector<std::unique_ptr<const CStatementList>>& basicBlocks);

}

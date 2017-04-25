#pragma once

#include <vector>
#include <bits/unique_ptr.h>
#include "../nodes/Statements.h"

namespace IRT {

    std::vector<std::unique_ptr<CStatementList>> divideTreeIntoBasicBlocks(const CStatement* tree);

}


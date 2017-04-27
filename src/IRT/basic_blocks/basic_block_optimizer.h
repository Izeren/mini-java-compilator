#pragma once

#include "../nodes/Statements.h"

namespace IRT {

    void optimizeBlocks(
            std::vector<std::unique_ptr<CStatementList>>& basicBlocks);

}

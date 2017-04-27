#pragma once

#include "../nodes/Statements.h"

namespace IRT {


    const CStatement* collectBlocksToTree(const std::vector<std::unique_ptr<CStatementList>>& blocks);

}
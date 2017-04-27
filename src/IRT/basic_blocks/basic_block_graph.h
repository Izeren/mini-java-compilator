#pragma once

#include <map>
#include <string>
#include "../nodes/Statements.h"
#include "../utils/Label.h"

namespace IRT {

    bool isCJumpBasicBlock(const CStatementList* basicBlock);

    std::string getFalseLabel(const CStatementList* basicBlock);

    bool isJumpBasicBlock(const CStatementList* basicBlock);

    std::string getJmpLabel(const CStatementList *basicBlock);

    std::string getBlockLabel(const CStatementList *basicBlock);

    std::vector<std::unique_ptr<CStatementList>> reorderByTracies(
            std::vector<std::unique_ptr<CStatementList>>& basicBlocks);

}

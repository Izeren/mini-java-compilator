#include <cassert>
#include "basic_block_optimizer.h"
#include "basic_block_graph.h"
#include "../nodes/Expressions.h"

namespace IRT {

    void optimizeBlocks(
            std::vector<std::unique_ptr<CStatementList>>& basicBlocks) {

        // delete jump "label"; label "label"
        for (int i = 0; i + 1 < basicBlocks.size(); ++i) {
            const CStatementList* block = basicBlocks[i].get();

            if (isCJumpBasicBlock(block)) {
                // do nothing
            } else if (isJumpBasicBlock(block)) {

                std::string jumpLabel = getJmpLabel(block);
                std::string nextBlockLabel = getBlockLabel(basicBlocks[i + 1].get());
                if (jumpLabel == nextBlockLabel) {
                    // delete jump
                    CStatementList* newStmList = block->CopyNotConst();
                    newStmList->StatementsNotConst().pop_back();

                    basicBlocks[i] = std::move(std::unique_ptr<CStatementList>(newStmList));
                }
            } else {
                // do nothing
            }
        }
    }

}

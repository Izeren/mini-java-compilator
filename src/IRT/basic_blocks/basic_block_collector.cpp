#include "basic_block_collector.h"

namespace IRT {

    const CStatement* collectBlocksToTree(const std::vector<std::unique_ptr<CStatementList>>& blocks) {
        CStatementList* tree = new CStatementList();

        for (int i = 0; i < blocks.size(); ++i) {
            CStatementList* blockList = blocks[i].get();

            for (int j = 0; j < blockList->Statements().size(); ++j) {
                tree->Add(std::move(blockList->Statements()[j]->Copy()));
            }
        }

        return tree;
    }

}

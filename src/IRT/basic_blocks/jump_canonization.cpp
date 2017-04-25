#include "jump_canonization.h"
#include "basic_block_divider.h"
#include "basic_block_graph.h"
#include "basic_block_optimizer.h"
#include "basic_block_collector.h"

namespace IRT {

    std::shared_ptr<MethodToIRTMap> canonizeJumps(std::shared_ptr<const MethodToIRTMap> trees) {
        std::shared_ptr<MethodToIRTMap> newTrees =
                std::shared_ptr<MethodToIRTMap>(std::move(std::unique_ptr<MethodToIRTMap>(new MethodToIRTMap())));
        for (auto tree = trees->begin(); tree != trees->end(); ++tree) {
            std::vector<std::unique_ptr<CStatementList>> basicBlocks =
                    divideTreeIntoBasicBlocks(tree->second.get());

            std::vector<std::unique_ptr<CStatementList>> reorderedBlocks =
                    reorderByTracies(basicBlocks);

            optimizeBlocks(reorderedBlocks);

            (*newTrees)[tree->first] = std::move(std::unique_ptr<const CStatement>(
                    collectBlocksToTree(reorderedBlocks)));
        }

        return newTrees;
    }

}

#include <cassert>
#include "basic_block_graphr.h"

namespace IRT {

    // label -> block index
    std::map<std::string, int> buildBasicBlocksGraph(
            const std::vector<std::unique_ptr<const CStatementList>>& basicBlocks) {
        std::map<std::string, int> graph;

        int noJmpBlocks = 0;

        for (int i = 0; i < basicBlocks.size(); ++i) {

        }

        assert(noJmpBlocks == 1);

        return graph;
    };

}

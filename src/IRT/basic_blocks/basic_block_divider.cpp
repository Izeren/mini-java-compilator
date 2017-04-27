#include <cassert>
#include "basic_block_divider.h"

#define MOVE_COPY(stm) std::move(stm->Copy())
#define SMOVE_UNIQ(stm) std::move(std::unique_ptr<const CStatement>(stm))
namespace IRT {

    bool isStmLabel(const CStatement* stm) {
        return dynamic_cast<const CLabelStatement*>(stm) != nullptr;
    }

    bool isStmJmp(const CStatement* stm) {
        return dynamic_cast<const CJumpStatement*>(stm) != nullptr;
    }

    bool isStmCjmp(const CStatement* stm) {
        return dynamic_cast<const CJumpConditionalStatement*>(stm) != nullptr;
    }

    std::vector<std::unique_ptr<CStatementList>> divideTreeIntoBasicBlocks(const CStatement* tree) {

        const CStatementList* stmList = dynamic_cast<const CStatementList*>(tree);
        assert(stmList != nullptr);

        std::vector<std::unique_ptr<CStatementList>> basicBlocks;
        CStatementList* basicBlock = new CStatementList();
        // first label always function name label
        basicBlock->Add(MOVE_COPY(stmList->Statements()[0]));

        bool isLastStmJmpOrCJmp = false;
        int stmListSize = (int) stmList->Statements().size();
        for  (int i = 1; i < stmListSize; ++i) {
            const CStatement* stm = stmList->Statements()[i].get();
            const CLabelStatement* labelStm = dynamic_cast<const CLabelStatement*>(stm);

            if (labelStm != nullptr) {
                if (isLastStmJmpOrCJmp) {
                    // OK
                } else {
                    // add to last block JMP to us
                    basicBlock->Add(SMOVE_UNIQ(new CJumpStatement(std::move(labelStm->CastCopy()))));
                }

                // finish basic block
                basicBlocks.push_back(std::unique_ptr<CStatementList>(basicBlock));
                // start new basic block
                basicBlock = new CStatementList();
                basicBlock->Add(MOVE_COPY(labelStm));

                isLastStmJmpOrCJmp = false;
            } else if (isStmJmp(stm) || isStmCjmp(stm)) {
                basicBlock->Add(MOVE_COPY(stm));
                if ((i + 1) == stmListSize || isStmLabel(stmList->Statements()[i + 1].get())) {
                    // OK
                    isLastStmJmpOrCJmp = true;
                } else {
                    // Seems that it can't happen
                    assert(false);
                    // finish basic block
                    basicBlocks.push_back(std::unique_ptr<CStatementList>(basicBlock));
                    // start new basic block
                    basicBlock = new CStatementList();
                    // add fake label
                    basicBlock->Add(std::unique_ptr<const CStatement>(new CLabelStatement(CLabel())));

                    isLastStmJmpOrCJmp = false;
                }
            } else {
                basicBlock->Add(MOVE_COPY(stm));

                isLastStmJmpOrCJmp = false;
            }
        }

        if (basicBlock->Statements().size() != 0) {
            basicBlocks.push_back(std::unique_ptr<CStatementList>(basicBlock));
        } else {
            assert(false);
        }

        return std::move(basicBlocks);
    }

}

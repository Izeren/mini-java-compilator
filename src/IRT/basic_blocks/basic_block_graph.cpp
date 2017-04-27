#include <cassert>
#include "basic_block_graph.h"

namespace IRT {

    // label -> block index
    std::map<std::string, int> buildLabelToBlockIndexMap(
            const std::vector<std::unique_ptr<CStatementList>> &basicBlocks) {
        std::map<std::string, int> labelToBlockIndexMap;

        for (int i = 0; i < basicBlocks.size(); ++i) {
            const CStatementList* stmList = basicBlocks[i].get();
            assert(stmList->Statements().size() != 0);

            const CLabelStatement* labelStatement =
                    dynamic_cast<const CLabelStatement*>(stmList->Statements()[0].get());
            assert(labelStatement != nullptr);

            assert(labelToBlockIndexMap.find(labelStatement->Label().ToString()) == labelToBlockIndexMap.end());

            labelToBlockIndexMap[labelStatement->Label().ToString()] = i;
        }

        return labelToBlockIndexMap;
    };

    bool isCJumpBasicBlock(const CStatementList* basicBlock) {
        assert(basicBlock != nullptr);
        assert(basicBlock->Statements().size() != 0);
        const CStatement* lastStm = basicBlock->Statements().back().get();

        return dynamic_cast<const CJumpConditionalStatement*>(lastStm) != nullptr;
    }

    std::string getFalseLabel(const CStatementList* basicBlock) {
        assert(basicBlock != nullptr);
        assert(basicBlock->Statements().size() != 0);
        const CStatement* lastStm = basicBlock->Statements().back().get();
        const CJumpConditionalStatement* cjump = dynamic_cast<const CJumpConditionalStatement*>(lastStm);
        assert(cjump != nullptr);

        return cjump->FalseLabel()->Label().ToString();
    }

    bool isJumpBasicBlock(const CStatementList* basicBlock) {
        assert(basicBlock != nullptr);
        assert(basicBlock->Statements().size() != 0);
        const CStatement* lastStm = basicBlock->Statements().back().get();

        return dynamic_cast<const CJumpStatement*>(lastStm) != nullptr;
    }

    std::string getJmpLabel(const CStatementList *basicBlock) {
        assert(basicBlock != nullptr);
        assert(basicBlock->Statements().size() != 0);
        const CStatement* lastStm = basicBlock->Statements().back().get();
        const CJumpStatement* jump = dynamic_cast<const CJumpStatement*>(lastStm);
        assert(jump != nullptr);

        return jump->getLabel()->Label().ToString();
    }

    std::string getBlockLabel(const CStatementList *basicBlock) {
        assert(basicBlock != nullptr);
        assert(basicBlock->Statements().size() != 0);
        const CStatement* firstStm = basicBlock->Statements().front().get();
        const CLabelStatement* label = dynamic_cast<const CLabelStatement*>(firstStm);
        assert(label != nullptr);

        return label->Label().ToString();
    }

    void dfs(const int index,
             const std::vector<std::unique_ptr<CStatementList>> &basicBlocks,
             std::map<std::string, int>& labelToBlockIndexMap,
             std::vector<bool>& usedBlocks,
             std::vector<int>& newOrder) {

        newOrder.push_back(index);
        usedBlocks[index] = true;

        const CStatementList* block = basicBlocks[index].get();

        if (isCJumpBasicBlock(block)) {
            std::string labelFalse = getFalseLabel(block);
            int falseIndex = labelToBlockIndexMap[labelFalse];
            if (!usedBlocks[falseIndex]) {
                dfs(falseIndex, basicBlocks, labelToBlockIndexMap, usedBlocks, newOrder);
                return;
            }

            assert(false);
        } else if (isJumpBasicBlock(block)) {
            std::string label = getJmpLabel(block);
            int jmpIndex = labelToBlockIndexMap[label];
            if (!usedBlocks[jmpIndex]) {
                dfs(jmpIndex, basicBlocks, labelToBlockIndexMap, usedBlocks, newOrder);
            }
        } else {
            // OK ?
        }
    }

    std::vector<int> getReorderedIndecies(const std::vector<std::unique_ptr<CStatementList>> &basicBlocks) {
        std::map<std::string, int> labelToBlockIndexMap = buildLabelToBlockIndexMap(basicBlocks);
        std::vector<bool> usedBlocks(basicBlocks.size(), false);

        std::vector<int> newOrder;

        // try use cjumps firstly
        for (int i = 0; i < basicBlocks.size(); ++i) {
            if (usedBlocks[i]) {
                continue;
            }

            if (!isCJumpBasicBlock(basicBlocks[i].get())) {
                continue;
            }

            dfs(i, basicBlocks, labelToBlockIndexMap, usedBlocks, newOrder);
        }

        // add not cjump
        for (int i = 0; i < basicBlocks.size(); ++i) {
            if (usedBlocks[i]) {
                continue;
            }

            dfs(i, basicBlocks, labelToBlockIndexMap, usedBlocks, newOrder);
        }

        assert(newOrder.size() == basicBlocks.size());
        return newOrder;
    }

    std::vector<std::unique_ptr<CStatementList>> reorderByTracies(
            std::vector<std::unique_ptr<CStatementList>>& basicBlocks) {

        std::vector<int> newOrder = getReorderedIndecies(basicBlocks);
        std::vector<std::unique_ptr<CStatementList>> reorderedBlocks(basicBlocks.size());
        for (int i = 0; i < newOrder.size(); ++i) {
            reorderedBlocks[i] = std::move(basicBlocks[newOrder[i]]);
        }

        return std::move(reorderedBlocks);
    }

}

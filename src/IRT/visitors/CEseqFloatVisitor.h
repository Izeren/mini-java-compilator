#pragma once

#include "IVisitor.h"
#include "../nodes/Expressions.h"
#include "../nodes/Statements.h"

namespace IRT {

    class CEseqFloatVisitor : public IVisitor {
    public:

        void Visit(const CEseqExpression &expression) override;

        void Visit(const CBinopExpression &expression) override;

        void Visit(const CConstExpression &expression) override;

        void Visit(const CTempExpression &expression) override;

        void Visit(const CNameExpression &expression) override;

        void Visit(const CCallExpression &expression) override;

        void Visit(const CMemExpression &expression) override;

        void Visit(const CExpressionList &expression) override;

        void Visit(const CMoveStatement &statement) override;

        void Visit(const CExpStatement &statement) override;

        void Visit(const CLabelStatement &statement) override;

        void Visit(const CJumpStatement &statement) override;

        void Visit(const CJumpConditionalStatement &statement) override;

        void Visit(const CSeqStatement &statement) override;

        void Visit(const CStatementList &statement) override;

        std::unique_ptr<const CStatement> getResultTree();

    private:

        void processCallArgument(
                const CExpression* argExp,
                CExpressionList* tempExpressionList,
                std::vector<std::unique_ptr<const CStatement>>& helpStatement);

        std::unique_ptr<const IRT::CExpression> processRightEseqInCBinop(
                const IRT::CBinopExpression *binop,
                const IRT::CExpression *left, const IRT::CEseqExpression *rightEseq);

        std::unique_ptr<const CStatement> processRightEseqInCJump(
                const CJumpConditionalStatement* cjump,
                const CExpression* left,
                const CEseqExpression* rightEseq);

        std::unique_ptr<const IRT::CStatement> processSourceEseqInCMove(
                const IRT::CExpression *target, const IRT::CEseqExpression *sourceEseq);


        std::unique_ptr<const CStatement> childStatement;

        std::unique_ptr<const CExpression> childExpression;

        std::unique_ptr<const CExpressionList> childExpressionList;
    };

}

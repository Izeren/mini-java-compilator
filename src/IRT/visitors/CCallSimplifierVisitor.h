#include <bits/unique_ptr.h>
#include "IVisitor.h"
#include "../nodes/Statements.h"
#include "../nodes/Expressions.h"

namespace IRT {

    class CCallSimplifierVisitor : public IVisitor {
    private:
        std::unique_ptr<const CStatement> childStatement;

        std::unique_ptr<const CExpression> childExpression;

        std::unique_ptr<const CExpressionList> childExpressionList;

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
    };

}
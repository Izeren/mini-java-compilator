//
// Created by izeren on 4/24/17.
//
#pragma once

#include <cassert>
#include <vector>

#include "../visitors/IVisitor.h"

#include "../nodes/Expressions.h"
#include "../nodes/Statements.h"

namespace IRT {

    class CLinearizeVisitor : public IRT::IVisitor {
    public:
        CLinearizeVisitor( );

        ~CLinearizeVisitor( );

        std::unique_ptr<const CStatement> getResultTree( );

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

    private:
        std::unique_ptr<CStatementList> statementList;
    };

}

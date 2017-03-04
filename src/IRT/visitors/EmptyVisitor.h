#pragma once

#include "IVisitor.h"

namespace IRT {

    class CEseqExpression;
    class CBinopExpression;
    class CConstExpression;
    class CTempExpression;
    class CNameExpression;
    class CCallExpression;
    class CMemExpression;
    class CExpressionList;

    class CMoveStatement;
    class CExpStatement;
    class CLabelStatement;
    class CJumpStatement;
    class CJumpConditionalStatement;
    class CSeqStatement;
    class CStatementList;

    class EmptyVisitor : public IVisitor {
    public:
        virtual void Visit( CEseqExpression &expression ) override;
        virtual void Visit( CBinopExpression &expression ) override;
        virtual void Visit( CConstExpression &expression ) override;
        virtual void Visit( CTempExpression &expression ) override;
        virtual void Visit( CNameExpression &expression ) override;
        virtual void Visit( CCallExpression &expression ) override;
        virtual void Visit( CMemExpression &expression ) override;
        virtual void Visit( CExpressionList &expression ) override;

        virtual void Visit( CMoveStatement &statement ) override;
        virtual void Visit( CExpStatement &statement ) override;
        virtual void Visit( CLabelStatement &statement ) override;
        virtual void Visit( CJumpStatement &statement ) override;
        virtual void Visit( CJumpConditionalStatement &statement ) override;
        virtual void Visit( CSeqStatement &statement ) override;
        virtual void Visit( CStatementList &statement ) override;

        virtual ~IVisitor() {};

    };

}

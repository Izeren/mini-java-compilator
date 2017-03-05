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
        virtual void Visit( const CEseqExpression &expression ) override;

        virtual void Visit( const CBinopExpression &expression ) override;

        virtual void Visit( const CConstExpression &expression ) override;

        virtual void Visit( const CTempExpression &expression ) override;

        virtual void Visit( const CNameExpression &expression ) override;

        virtual void Visit( const CCallExpression &expression ) override;

        virtual void Visit( const CMemExpression &expression ) override;

        virtual void Visit( const CExpressionList &expression ) override;

        virtual void Visit( const CMoveStatement &statement ) override;

        virtual void Visit( const CExpStatement &statement ) override;

        virtual void Visit( const CLabelStatement &statement ) override;

        virtual void Visit( const CJumpStatement &statement ) override;

        virtual void Visit( const CJumpConditionalStatement &statement ) override;

        virtual void Visit( const CSeqStatement &statement ) override;

        virtual void Visit( const CStatementList &statement ) override;

    };

}

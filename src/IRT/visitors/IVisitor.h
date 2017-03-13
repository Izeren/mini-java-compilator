#pragma once
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

    class IVisitor {
    public:
        virtual void Visit( const CEseqExpression &expression ) = 0;

        virtual void Visit( const CBinopExpression &expression ) = 0;

        virtual void Visit( const CConstExpression &expression ) = 0;

        virtual void Visit( const CTempExpression &expression ) = 0;

        virtual void Visit( const CNameExpression &expression ) = 0;

        virtual void Visit( const CCallExpression &expression ) = 0;

        virtual void Visit( const CMemExpression &expression ) = 0;

        virtual void Visit( const CExpressionList &expression ) = 0;

        virtual void Visit( const CMoveStatement &statement ) = 0;

        virtual void Visit( const CExpStatement &statement ) = 0;

        virtual void Visit( const CLabelStatement &statement ) = 0;

        virtual void Visit( const CJumpStatement &statement ) = 0;

        virtual void Visit( const CJumpConditionalStatement &statement ) = 0;

        virtual void Visit( const CSeqStatement &statement ) = 0;

        virtual void Visit( const CStatementList &statement ) = 0;

        virtual ~IVisitor() {};

    };

}

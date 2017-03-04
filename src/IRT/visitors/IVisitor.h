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
        virtual void Visit( CEseqExpression &expression ) = 0;
        virtual void Visit( CBinopExpression &expression ) = 0;
        virtual void Visit( CConstExpression &expression ) = 0;
        virtual void Visit( CTempExpression &expression ) = 0;
        virtual void Visit( CNameExpression &expression ) = 0;
        virtual void Visit( CCallExpression &expression ) = 0;
        virtual void Visit( CMemExpression &expression ) = 0;
        virtual void Visit( CExpressionList &expression ) = 0;

        virtual void Visit( CMoveStatement &statement ) = 0;
        virtual void Visit( CExpStatement &statement ) = 0;
        virtual void Visit( CLabelStatement &statement ) = 0;
        virtual void Visit( CJumpStatement &statement ) = 0;
        virtual void Visit( CJumpConditionalStatement &statement ) = 0;
        virtual void Visit( CSeqStatement &statement ) = 0;
        virtual void Visit( CStatementList &statement ) = 0;

        virtual ~IVisitor() {};

    };

}

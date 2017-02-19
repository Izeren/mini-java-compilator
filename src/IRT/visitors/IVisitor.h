#pragma once

// Expression Nodes of the IRT
class CEseqExpression;
class CBinopExpression;
class CConstExpression;
class CTempExpression;
class CNameExpression;
class CCallExpression;
class CMemExpression;
class CExpressionList;

// Statement Nodes of the IRT
class CMoveStatement;
class CExpStatement;
class CLabelStatement;
class CJumpStatement;
class CSequenceStatement;
class CStatementList;

namespace IRT {
    class IVisitor {
    public:
        //Expressions visit methods
        virtual ~IVisitor( CEseqExpression &expression ) = 0;
        virtual ~IVisitor( CBinopExpression &expression ) = 0;
        virtual ~IVisitor( CConstExpression &expression ) = 0;
        virtual ~IVisitor( CTempExpression &expression ) = 0;
        virtual ~IVisitor( CNameExpression &expression ) = 0;
        virtual ~IVisitor( CCallExpression &expression ) = 0;
        virtual ~IVisitor( CMemExpression &expression ) = 0;
        virtual ~IVisitor( CExpressionList &expression ) = 0;

        //Statement visit methods
        virtual ~IVisitor( CMoveStatement &statement ) = 0;
        virtual ~IVisitor( CExpStatement &statement ) = 0;
        virtual ~IVisitor( CLabelStatement &statement ) = 0;
        virtual ~IVisitor( CJumpStatement &statement ) = 0;
        virtual ~IVisitor( CSequenceStatement &statement ) = 0;
        virtual ~IVisitor( CStatementList &statement ) = 0;

    };

}

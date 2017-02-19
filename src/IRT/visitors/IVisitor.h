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
        virtual Visit( CEseqExpression &expression ) = 0;
        virtual Visit( CBinopExpression &expression ) = 0;
        virtual Visit( CConstExpression &expression ) = 0;
        virtual Visit( CTempExpression &expression ) = 0;
        virtual Visit( CNameExpression &expression ) = 0;
        virtual Visit( CCallExpression &expression ) = 0;
        virtual Visit( CMemExpression &expression ) = 0;
        virtual Visit( CExpressionList &expression ) = 0;

        //Statement visit methods
        virtual Visit( CMoveStatement &statement ) = 0;
        virtual Visit( CExpStatement &statement ) = 0;
        virtual Visit( CLabelStatement &statement ) = 0;
        virtual Visit( CJumpStatement &statement ) = 0;
        virtual Visit( CSequenceStatement &statement ) = 0;
        virtual Visit( CStatementList &statement ) = 0;

        virtual ~IVisitor() {};

    };

}

//
// Created by izeren on 2/19/17.
//
#pragma  once

#include "INode.h"

namespace  IRT {

    class IExpression : public  INode {
    public:
        virtual ~IExpression();
    };

    class CExpression : public IExpression {
    public:
        virtual void Accept( IVisitor& visitor ) const = 0;
    };

    class CEseqExpression : public CExpression {

    };
    class CBinopExpression : public  CExpression {

    };
    class CConstExpression : public CExpression {

    };
    class CTempExpression : public CExpression {

    };
    class CNameExpression : public CExpression {

    };
    class CCallExpression : public CExpression{

    };
    class CMemExpression : public CExpression {

    };
    class CExpressionList : CExpression {

    };



}
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
        void Accept( IVisitor* visitor ) const override;
    };

}
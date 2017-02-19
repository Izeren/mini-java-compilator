#pragma once

#include <memory>
#include "INode.h"

namespace IRT {

    class IStatement : public INode {
        // inherited
    };

    class CStatement : public IStatement {
    public:
        CStatement();

        void Accept( IVisitor* visitor ) const override;
    };

    enum class TLogicOperator : char {
        EQUALS,
        NOT_EQUALS,
        LESS,
        GREATER,
        LESS_OR_EQUAL,
        GREATER_OR_EQUAL,
        ULT, // ???
        ULE, // ???
        UGT, // ???
        UGE // ???
    };


    class CExpression;

    class CMoveStatement : public CStatement {
    public:

        CMoveStatement( std::unique_ptr< const CExpression> _target, std::unique_ptr< const CExpression> _source);

        const CExpression* Target() const;

        const CExpression* Source() const;

    private:
        std::unique_ptr<const CExpression> target;
        std::unique_ptr<const CExpression> source;
    };

}
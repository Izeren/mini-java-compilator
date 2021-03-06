//
// Created by izeren on 2/27/17.
//
#pragma once
#include <cassert>
#include <memory>
#include "Label.h"
#include "../nodes/Expressions.h"
#include "../nodes/Statements.h"

namespace IRT {

// Basic subtree wrappers

    class ISubtreeWrapper {
    public:
        virtual std::unique_ptr<const CExpression> ToExpression() = 0;
        virtual std::unique_ptr<const CStatement> ToStatement() = 0;
        virtual std::unique_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) = 0;
    };

    class CExpressionWrapper : public ISubtreeWrapper {
    public:
        explicit CExpressionWrapper( const CExpression* _expression )
                : expression( _expression ) {}
        explicit CExpressionWrapper( std::unique_ptr<const CExpression> _expression )
                : expression( std::move( _expression ) ) {}
        virtual ~CExpressionWrapper() {};

        virtual std::unique_ptr<const CExpression> ToExpression() override;
        virtual std::unique_ptr<const CStatement> ToStatement() override;
        virtual std::unique_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
    private:
        std::unique_ptr<const CExpression> expression;
    };

    class CStatementWrapper : public ISubtreeWrapper {
    public:
        explicit CStatementWrapper( const CStatement* _statement )
                : statement( _statement ) {}
        explicit CStatementWrapper( std::unique_ptr<const CStatement> _statement ) : statement( std::move( _statement ) ) {}

        virtual std::unique_ptr<const CExpression> ToExpression() override;
        virtual std::unique_ptr<const CStatement> ToStatement() override;
        virtual std::unique_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
    private:
        std::unique_ptr<const CStatement> statement;
    };

    class CConditionalWrapper : public ISubtreeWrapper {
    public:

        virtual std::unique_ptr<const CExpression> ToExpression() override;
        virtual std::unique_ptr<const CStatement> ToStatement() override;
        virtual std::unique_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) = 0;
    };


// Additional wrappers

    class CRelativeConditionalWrapper : public CConditionalWrapper {
    public:
        CRelativeConditionalWrapper(
                enums::TLogicOperator _operator,
                const CExpression* _operandLeft,
                const CExpression* _operandRight
        ) : operatorType( _operator ),
            operandLeft( _operandLeft ),
            operandRight( _operandRight ) {}

        CRelativeConditionalWrapper(
                enums::TLogicOperator _operatorType,
                std::unique_ptr<const CExpression> _operandLeft,
                std::unique_ptr<const CExpression> _operandRight
        ) : operatorType( _operatorType ),
            operandLeft( std::move( _operandLeft ) ),
            operandRight( std::move( _operandRight ) ) {}

        virtual std::unique_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
    private:
        enums::TLogicOperator operatorType;
        std::unique_ptr<const CExpression> operandLeft;
        std::unique_ptr<const CExpression> operandRight;
    };

    class CAndConditionalWrapper : public CConditionalWrapper {
    public:
        CAndConditionalWrapper( std::unique_ptr<ISubtreeWrapper> _operandLeft, std::unique_ptr<ISubtreeWrapper> _operandRight )
                : operandLeft( std::move( _operandLeft ) ), operandRight( std::move( _operandRight ) ) {}

        virtual std::unique_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
    private:
        std::unique_ptr<ISubtreeWrapper> operandLeft;
        std::unique_ptr<ISubtreeWrapper> operandRight;
    };

    class COrConditionalWrapper : public CConditionalWrapper {
    public:
        COrConditionalWrapper( std::unique_ptr<ISubtreeWrapper> _operandLeft, std::unique_ptr<ISubtreeWrapper> _operandRight )
                : operandLeft( std::move( _operandLeft ) ), operandRight( std::move( _operandRight ) ) {}

        virtual std::unique_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
    private:
        std::unique_ptr<ISubtreeWrapper> operandLeft;
        std::unique_ptr<ISubtreeWrapper> operandRight;
    };

    class CNegateConditionalWrapper : public CConditionalWrapper {
    public:
        CNegateConditionalWrapper( std::unique_ptr<ISubtreeWrapper> _wrapper )
                : wrapper( std::move( _wrapper ) ) {}

        virtual std::unique_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
    private:
        std::unique_ptr<ISubtreeWrapper> wrapper;
    };

}


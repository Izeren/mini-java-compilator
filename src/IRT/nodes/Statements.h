#pragma once

#include <memory>
#include "INode.h"

namespace IRT {

    class IStatement : public INode {
    public:
        virtual void Accept( IVisitor &visitor ) override;
    };

    class CStatement : public IStatement {
    public:
        virtual void Accept( IVisitor &visitor ) override;
    };


    class CExpression;

// ********************************************************************************

    class CMoveStatement : public CStatement {
    public:

        CMoveStatement( std::unique_ptr<const CExpression> _target, std::unique_ptr<const CExpression> _source );

        const CExpression *Target( ) const;

        const CExpression *Source( ) const;

        virtual void Accept( IVisitor &visitor ) override;

    private:
        std::unique_ptr<const CExpression> target;
        std::unique_ptr<const CExpression> source;
    };

// ***************************************************************************

    class CExpStatement : public CStatement {
    public:

        CExpStatement( std::unique_ptr<const CExpression> _expression );

        const CExpression *Expression( ) const;

        virtual void Accept( IVisitor &visitor ) override;

    private:
        std::unique_ptr<const CExpression> expression;
    };

// ***************************************************************************

    class CJumpStatement : public CStatement {
    public:

        CJumpStatement( CLabel _target );

        CLabel Target( ) const;

        virtual void Accept( IVisitor &visitor ) override;

    private:
        CLabel target;
    };

// ********************************************************************************

    class CJumpConditionalStatement : public CStatement {
    public:

        CJumpConditionalStatement( TLogicOperator _operation,
                                   std::unique_ptr<const CExpression> left, std::unique_ptr<const CExpression> right,
                                   CLabel _labelTrue, CLabel _labelFalse );

        const CExpression *LeftOperand( ) const;

        const CExpression *RightOperand( ) const;

        CLabel TrueLabel( ) const;

        CLabel FalseLabel( ) const;

        TLogicOperator Operation( );

        virtual void Accept( IVisitor &visitor ) override;

    private:
        std::unique_ptr<const CExpression> leftOperand;
        std::unique_ptr<const CExpression> rightOperand;
        CLabel labelTrue;
        CLabel labelFalse;
        TLogicOperator operation;
    };

// ********************************************************************************

    class CSeqStatement : public CStatement {
    public:

        CSeqStatement( std::unique_ptr<const CStatement> _left, std::unique_ptr<const CStatement> _right );

        const CStatement *LeftStatement( ) const;

        const CStatement *RightStatement( ) const;

        virtual void Accept( IVisitor &visitor ) override;

    private:
        std::unique_ptr<const CStatement> leftStatement;
        std::unique_ptr<const CStatement> rightStatement;
    };

// ********************************************************************************

    class CLabelStatement : public CStatement {
    public:

        CLabelStatement( CLabel _label );

        CLabel Label( ) const;

        virtual void Accept( IVisitor &visitor ) override;

    private:
        CLabel label;
    };

// ********************************************************************************

    class CStatementList : public INode {
    public:
        CStatementList( );

        CStatementList( std::unique_ptr<const CStatement> statement );

        void Add( std::unique_ptr<const CStatement> &statement );

        const std::vector <std::unique_ptr<const CStatement>> &Statements( ) const;

        void Accept( IVisitor *visitor ) const override;

    private:
        std::vector <std::unique_ptr<const CStatement>> statements;
    };

}

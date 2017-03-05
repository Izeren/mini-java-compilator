#pragma once

#include <memory>
#include <vector>
#include "INode.h"
#include "../utils/Label.h"
#include "../utils/enums.h"

using namespace IRT::enums;

namespace IRT {

    class IStatement : public INode {
    };

    class CStatement : public IStatement {
    public:

        virtual std::unique_ptr<const CStatement> Copy( ) const = 0;

        virtual std::unique_ptr<const CStatement> Canonicalize( ) const = 0;
    };

    class CExpression;

// ********************************************************************************

    class CMoveStatement : public CStatement {
    public:

        CMoveStatement( std::unique_ptr<const CExpression> _target, std::unique_ptr<const CExpression> _source );

        const CExpression *Target( ) const;

        const CExpression *Source( ) const;

        virtual void Accept( IVisitor &visitor ) override;

        std::unique_ptr<const CStatement> Copy( ) const override;

        std::unique_ptr<const CStatement> Canonicalize( ) const override;

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

        std::unique_ptr<const CStatement> Copy( ) const override;

        std::unique_ptr<const CStatement> Canonicalize( ) const override;

    private:
        std::unique_ptr<const CExpression> expression;
    };

// ***************************************************************************

    class CJumpStatement : public CStatement {
    public:

        CJumpStatement( CLabel _target );

        CLabel Target( ) const;

        virtual void Accept( IVisitor &visitor ) override;

        std::unique_ptr<const CStatement> Copy( ) const override;

        std::unique_ptr<const CStatement> Canonicalize( ) const override;

    private:
        CLabel target;
    };

// ********************************************************************************

    class CJumpConditionalStatement : public CStatement {
    public:

        CJumpConditionalStatement( TLogicOperator _operation,
                                   std::unique_ptr<const CExpression> left, std::unique_ptr<const CExpression> right,
                                   std::unique_ptr<const CLabelStatement> _labelTrue,
                                   std::unique_ptr<const CLabelStatement> _labelFalse );

        const CExpression *LeftOperand( ) const;

        const CExpression *RightOperand( ) const;

        const CLabelStatement *TrueLabel( ) const;

        const CLabelStatement *FalseLabel( ) const;

        TLogicOperator Operation( );

        virtual void Accept( IVisitor &visitor ) override;

        std::unique_ptr<const CStatement> Copy( ) const override;

        std::unique_ptr<const CStatement> Canonicalize( ) const override;

    private:
        std::unique_ptr<const CExpression> leftOperand;
        std::unique_ptr<const CExpression> rightOperand;
        std::unique_ptr<const CLabelStatement> labelTrue;
        std::unique_ptr<const CLabelStatement> labelFalse;
        TLogicOperator operation;
    };

// ********************************************************************************

    class CSeqStatement : public CStatement {
    public:

        CSeqStatement( std::unique_ptr<const CStatement> _left, std::unique_ptr<const CStatement> _right );

        const CStatement *LeftStatement( ) const;

        const CStatement *RightStatement( ) const;

        virtual void Accept( IVisitor &visitor ) override;

        std::unique_ptr<const CStatement> Copy( ) const override;

        std::unique_ptr<const CStatement> Canonicalize( ) const override;

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

        std::unique_ptr<const CStatement> Copy( ) const override;

        std::unique_ptr<const CStatement> Canonicalize( ) const override;

    private:
        CLabel label;
    };

// ********************************************************************************

    class CStatementList : public CStatement {
    public:
        CStatementList( );

        CStatementList( std::unique_ptr<const CStatement> &statement );

        void Add( std::unique_ptr<const CStatement> &statement );

        const std::vector<std::unique_ptr<const CStatement>> &Statements( ) const;

        virtual void Accept( IVisitor &visitor ) override;

        std::unique_ptr<const CStatement> Copy( ) const override;

        std::unique_ptr<const CStatement> Canonicalize( ) const override;

    private:
        std::vector<std::unique_ptr<const CStatement>> statements;
    };

}

//
// Created by izeren on 2/19/17.
//
#pragma  once

#include <memory>
#include "INode.h"
#include "../utils/enums.h"
#include "../utils/Label.h"
#include "../utils/Temporary.h"
#include <vector>


namespace IRT {
    class CStatement;
//------------------------------------------------------------------------------------------
    class IExpression : public INode {
    public:
        virtual ~IExpression() {};

        virtual void Accept( IVisitor &visitor ) const = 0;
    };

//------------------------------------------------------------------------------------------
    class CExpression : public IExpression {
    public:
        virtual ~CExpression() {};

        virtual void Accept( IVisitor &visitor ) const = 0;
    };

//------------------------------------------------------------------------------------------
    class CEseqExpression : public CExpression {
    public:
        const CStatement *getStatement() const;

        CEseqExpression( std::unique_ptr<const CStatement> _statement,
                         std::unique_ptr<const CExpression> _expression );

        const CExpression *getExpression() const;

        virtual void Accept( IVisitor &visitor ) const override;

        virtual ~CEseqExpression();

    private:
        std::unique_ptr<const CStatement> statement;
        std::unique_ptr<const CExpression> expression;
    };

//------------------------------------------------------------------------------------------
    class CBinopExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) const override;

        CBinopExpression(  std::unique_ptr<const CExpression> _leftOperand,
                           std::unique_ptr<const CExpression> _rightOperand, enums::TOperationType _operation );

        const CExpression *getLeftOperand() const;

        const CExpression *getRightOperand() const;

        enums::TOperationType getOperation() const;

        virtual ~CBinopExpression();

    private:
        std::unique_ptr<const CExpression> leftOperand;
        std::unique_ptr<const CExpression> rightOperand;
        enums::TOperationType operation;

    };

//------------------------------------------------------------------------------------------
    class CConstExpression : public CExpression {
    public:
        int getValue() const;

        CConstExpression( int _value );

        virtual void Accept( IVisitor &visitor ) const override;

        virtual ~CConstExpression();

    private:
        int value;
    };

//------------------------------------------------------------------------------------------
    class CTempExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) const override;

        const CTemp &getTemprorary() const;

        CTempExpression( const CTemp &_temprorary );

        virtual ~CTempExpression();

    private:
        CTemp temprorary;
    };

//------------------------------------------------------------------------------------------
    class CNameExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) const override;

        const CLabel &getLabel() const;

        CNameExpression( const CLabel &_label );

        virtual ~CNameExpression();

    private:
        CLabel label;
    };

//------------------------------------------------------------------------------------------
    class CCallExpression : public CExpression {
    public:
        CCallExpression(  std::unique_ptr<const CExpression> _function,
                          std::unique_ptr<const CExpressionList> _argumetns );

        const CExpression *getFunction() const;

        const CExpressionList *getArgumetns() const;

        virtual void Accept( IVisitor &visitor ) const override;

        virtual ~CCallExpression();

    private:
        std::unique_ptr<const CExpression> function;
        std::unique_ptr<const CExpressionList> argumetns;
    };

//------------------------------------------------------------------------------------------
    class CMemExpression : public CExpression {
    public:
        CMemExpression(  std::unique_ptr<const CExpression> _address );

        const CExpression *getAddress() const;

        virtual void Accept( IVisitor &visitor ) const override;

        virtual ~CMemExpression();

    private:
        std::unique_ptr<const CExpression> address;
    };

//------------------------------------------------------------------------------------------
    class CExpressionList : CExpression {
    public:
        CExpressionList() = default;

        CExpressionList( const CExpression *_expression );

        CExpressionList( std::unique_ptr<const CExpression> _expression );

        void Add( const CExpression *_expression );

        void Add( std::unique_ptr<const CExpression> _expression );

        const std::vector<std::unique_ptr<const CExpression>> &getExpressions() const;

        virtual void Accept( IVisitor &visitor ) const override;

        virtual ~CExpressionList();

    private:
        std::vector<std::unique_ptr<const CExpression>> expressions;
    };


}
//
// Created by izeren on 2/19/17.
//
#pragma  once

#include <zconf.h>
#include <bits/unique_ptr.h>
#include "INode.h"
#include "../utils/enums.h"

namespace IRT {

    class IExpression : public INode {
    public:
        virtual ~IExpression() {};
        virtual void Accept( IVisitor &visitor ) = 0;
    };

    class CExpression : public IExpression {
    public:
        virtual ~CExpression() {};
        virtual void Accept( IVisitor &visitor ) = 0;
    };

    class CEseqExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) override;

        virtual ~CEseqExpression();

    private:
        std::unique_ptr<const CStatement> statement;
        std::unique_ptr<const CExpression> expression;
    };

    class CBinopExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) override;

        virtual ~CBinopExpression();

    private:
        std::unique_ptr<const CExpression> leftOperand;
        std::unique_ptr<const CExpression> rightOperand;
        enums::TOperationType operaion;

    };

    class CConstExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) override;

        virtual ~CConstExpression();

    private:
        int value;
    };

    class CTempExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) override;

        virtual ~CTempExpression();

    private:
        CTemp temprorary;
    };

    class CNameExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) override;

        virtual ~CNameExpression();

    private:
        CLabel label;
    };

    class CCallExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) override;

        virtual ~CCallExpression();

    private:
        std::unique_ptr<const CExpression> function;
        std::unique_ptr<const CExpressionList> argumetns;
    };

    class CMemExpression : public CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) override;

        virtual ~CMemExpression();

    private:
        std::unique_ptr<const CExpression> address;
    };

    class CExpressionList : CExpression {
    public:
        virtual void Accept( IVisitor &visitor ) override;

        virtual ~CExpressionList();
    };


}
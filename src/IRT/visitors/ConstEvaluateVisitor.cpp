#include <cassert>
#include "ConstEvaluateVisitor.h"

#define SMOVE_UNIQ(value) std::move(std::unique_ptr<const CStatement>(value))
#define EMOVE_UNIQ(value) std::move(std::unique_ptr<const CExpression>(value))
#define M(value) std::move(value)
#define EXP std::unique_ptr<const CExpression>
#define STM std::unique_ptr<const CStatement>

int calculate(int left, int right, IRT::enums::TOperationType type) {
    switch (type) {
        case IRT::enums::TOperationType::PLUS:
            return left + right;
        case IRT::enums::TOperationType::MINUS:
            return left - right;
        case IRT::enums::TOperationType::MULTYPLY:
            return left * right;
        case IRT::enums::TOperationType::MOD:
            assert(right != 0);
            return left % right;
        default:
            assert(false);
    }
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CEseqExpression &expression) {
    assert(false);
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CBinopExpression &expression) {
    expression.getLeftOperand()->Accept(*this);
    EXP left = M(childExpression);

    expression.getRightOperand()->Accept(*this);
    EXP right = M(childExpression);

    const CConstExpression* leftConst = dynamic_cast<const CConstExpression*>(left.get());
    const CConstExpression* rightConst = dynamic_cast<const CConstExpression*>(right.get());

    if (leftConst != nullptr && rightConst != nullptr) {
        childExpression = EMOVE_UNIQ(new CConstExpression(
                calculate(leftConst->getValue(), rightConst->getValue(), expression.getOperation())
        ));
    } else {
        childExpression = EMOVE_UNIQ(new CBinopExpression(
                M(left),
                M(right),
                expression.getOperation()
        ));
    }
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CConstExpression &expression) {
    childExpression = M(expression.Copy());
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CTempExpression &expression) {
    childExpression = M(expression.Copy());
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CNameExpression &expression) {
    childExpression = M(expression.Copy());
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CCallExpression &expression) {
    expression.getArguments()->Accept(*this);

    childExpression = EMOVE_UNIQ(new CCallExpression(
            M(expression.getFunction()->CopyCast()),
            M(childExpressionList)
    ));
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CMemExpression &expression) {
    expression.getAddress()->Accept(*this);

    childExpression = EMOVE_UNIQ(new CMemExpression(
            M(childExpression)
    ));
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CExpressionList &expression) {
    CExpressionList* list = new CExpressionList();
    for (int i = 0; i < expression.getExpressions().size(); ++i) {
        expression.getExpressions()[i]->Accept((*this));
        list->Add(M(childExpression));
    }

    childExpressionList = M(std::unique_ptr<const CExpressionList>(list));
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CMoveStatement &statement) {
    statement.Target()->Accept(*this);
    EXP target = M(childExpression);

    statement.Source()->Accept(*this);
    EXP source = M(childExpression);

    childStatement = SMOVE_UNIQ(new CMoveStatement(
            M(target),
            M(source)
    ));
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CExpStatement &statement) {
    statement.Expression()->Accept(*this);
    childStatement = SMOVE_UNIQ(new CExpStatement(
            M(childExpression)
    ));
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CLabelStatement &statement) {
    childStatement = M(statement.Copy());
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CJumpStatement &statement) {
    childStatement = SMOVE_UNIQ(statement.Copy());
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CJumpConditionalStatement &statement) {
    statement.LeftOperand()->Accept(*this);
    EXP left = M(childExpression);

    statement.RightOperand()->Accept(*this);
    EXP right = M(childExpression);

    childStatement = SMOVE_UNIQ(new CJumpConditionalStatement(
            statement.Operation(),
            M(left),
            M(right),
            M(statement.TrueLabel()->CastCopy()),
            M(statement.FalseLabel()->CastCopy())
    ));
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CSeqStatement &statement) {
    assert(false);
}

void IRT::ConstEvaluateVisitor::Visit(const IRT::CStatementList &statement) {
    CStatementList* list = new CStatementList();
    for (int i = 0; i < statement.Statements().size(); ++i) {
        statement.Statements()[i]->Accept(*this);
        list->Add(M(childStatement));
    }

    result = M(std::unique_ptr<const CStatementList>(list));
}

std::unique_ptr<const IRT::CStatementList> IRT::ConstEvaluateVisitor::getResult() {
    return M(result);
}

#undef EMOVE_UNIQ
#undef SMOVE_UNIQ
#undef M
#undef STM
#undef EXP
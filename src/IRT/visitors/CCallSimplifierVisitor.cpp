#include <cassert>
#include "CCallSimplifierVisitor.h"
#include "../nodes/Expressions.h"
#include "../nodes/Statements.h"

void IRT::CCallSimplifierVisitor::Visit(const CEseqExpression &expression) {
    expression.getStatement()->Accept(*this);
    expression.getExpression()->Accept(*this);

    childExpression = std::unique_ptr<const CExpression>(
            new CEseqExpression(std::move(childStatement), std::move(childExpression))
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CBinopExpression &expression) {
    expression.getLeftOperand()->Accept(*this);
    std::unique_ptr<const CExpression> leftExpression = std::move(childExpression);

    expression.getRightOperand()->Accept(*this);
    std::unique_ptr<const CExpression> rightExpression = std::move(childExpression);

    childExpression = std::move(
            std::unique_ptr<const CExpression>(
                new CBinopExpression(
                        std::move(leftExpression),
                        std::move(rightExpression),
                        expression.getOperation()
                )
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CConstExpression &expression) {
    childExpression = std::move(expression.Copy());
}

void IRT::CCallSimplifierVisitor::Visit(const CTempExpression &expression) {
    childExpression = std::move(expression.Copy());
}

void IRT::CCallSimplifierVisitor::Visit(const CNameExpression &expression) {
    childExpression = std::move(expression.Copy());
}

void IRT::CCallSimplifierVisitor::Visit(const CCallExpression &expression) {
    expression.getArguments()->Accept(*this);

    CTemp temp;

    std::unique_ptr<const CExpression> callExp = std::unique_ptr<const CExpression>(
            new CCallExpression(
                    std::move(expression.getFunction()->CopyCast()),
                    std::move(childExpressionList)
            )
    );

    std::unique_ptr<const CStatement> moveStm = std::unique_ptr<const CStatement>(
            new CMoveStatement(
                    std::move(std::unique_ptr<const CExpression>(new CTempExpression(temp))),
                    std::move(callExp)
            )
    );

    childExpression = std::move(
            std::unique_ptr<const CExpression>(
                new CEseqExpression(
                    std::move(moveStm),
                    std::move(std::unique_ptr<const CExpression>(new CTempExpression(temp)))
                )
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CMemExpression &expression) {
    expression.getAddress()->Accept(*this);

    childExpression = std::move(
            std::unique_ptr<const CExpression>(
                new CMemExpression(
                        std::move(childExpression)
                )
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CExpressionList &expression) {
    CExpressionList* newExpressionList = new CExpressionList();
    for (int i = 0; i < expression.getExpressions().size(); ++i) {
        expression.getExpressions()[i]->Accept(*this);
        newExpressionList->Add(std::move(childExpression));
    }

    childExpressionList = std::move(
            std::unique_ptr<const CExpressionList>(
                    newExpressionList
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CMoveStatement &statement) {
    statement.Target()->Accept(*this);
    std::unique_ptr<const CExpression> target = std::move(childExpression);

    statement.Source()->Accept(*this);
    std::unique_ptr<const CExpression> source = std::move(childExpression);

    childStatement = std::move(
            std::unique_ptr<const CStatement>(
                    new CMoveStatement(
                        std::move(target),
                        std::move(source)
                    )
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CExpStatement &statement) {
    statement.Expression()->Accept(*this);

    childStatement = std::move(
            std::unique_ptr<const CStatement>(
                    new CExpStatement(std::move(childExpression))
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CLabelStatement &statement) {
    childStatement = std::move(statement.Copy());
}

void IRT::CCallSimplifierVisitor::Visit(const CJumpStatement &statement) {
    childStatement = std::move(
            std::unique_ptr<const CStatement>(
                    new CJumpStatement(
                            std::move(statement.getLabel()->CastCopy())
                    )
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CJumpConditionalStatement &statement) {
    statement.LeftOperand()->Accept(*this);
    std::unique_ptr<const CExpression> left = std::move(childExpression);

    statement.RightOperand()->Accept(*this);
    std::unique_ptr<const CExpression> right = std::move(childExpression);

    childStatement = std::move(
            std::unique_ptr<const CStatement>(
                    new CJumpConditionalStatement(
                            statement.Operation(),
                            std::move(left),
                            std::move(right),
                            std::move(statement.TrueLabel()->CastCopy()),
                            std::move(statement.FalseLabel()->CastCopy())
                    )
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CSeqStatement &statement) {
    statement.LeftStatement()->Accept(*this);
    std::unique_ptr<const CStatement> left = std::move(childStatement);

    statement.RightStatement()->Accept(*this);
    std::unique_ptr<const CStatement> right = std::move(childStatement);

    childStatement = std::move(
            std::unique_ptr<const CStatement>(
                    new CSeqStatement(
                            std::move(left),
                            std::move(right)
                    )
            )
    );
}

void IRT::CCallSimplifierVisitor::Visit(const CStatementList &statement) {
    assert(false);
}

std::unique_ptr<const IRT::CStatement> IRT::CCallSimplifierVisitor::getResultTree() {
    return std::move(childStatement);
}

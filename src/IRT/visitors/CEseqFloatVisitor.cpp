#include <cassert>
#include "CEseqFloatVisitor.h"

#define CAST_TO_ESEQ(exp) dynamic_cast<const CEseqExpression*>(exp)
#define SMOVE_UNIQ(value) std::move(std::unique_ptr<const CStatement>(value))
#define EMOVE_UNIQ(value) std::move(std::unique_ptr<const CExpression>(value))


bool isUselessConstStm(const IRT::CStatement* stm) {
    const IRT::CExpStatement* expStm = dynamic_cast<const IRT::CExpStatement*>(stm);

    return expStm != nullptr && dynamic_cast<const IRT::CConstExpression*>(expStm->Expression()) != nullptr;
}

bool isExpCommuteWithStm(const IRT::CExpression* exp, const IRT::CStatement* stm) {
    return isUselessConstStm(stm)
           || dynamic_cast<const IRT::CConstExpression*>(exp) != nullptr
           || dynamic_cast<const IRT::CNameExpression*>(exp) != nullptr;
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CEseqExpression &expression) {
    expression.getStatement()->Accept(*this);
    std::unique_ptr<const CStatement> stm = std::move(childStatement);

    expression.getExpression()->Accept(*this);
    std::unique_ptr<const CExpression> exp = std::move(childExpression);

    const CEseqExpression* eseq = CAST_TO_ESEQ(exp.get());
    if (eseq == nullptr) {
        childExpression = EMOVE_UNIQ( new CEseqExpression(
                std::move(stm),
                std::move(exp)
        ));
    } else {
        childExpression = EMOVE_UNIQ( new CEseqExpression(
                SMOVE_UNIQ(new CSeqStatement(
                        std::move(stm),
                        std::move(eseq->getStatement()->Copy())
                )),
                std::move(eseq->getExpression()->Copy())
        ));
    }
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CBinopExpression &expression) {
    expression.getLeftOperand()->Accept(*this);
    std::unique_ptr<const CExpression> left = std::move(childExpression);

    expression.getRightOperand()->Accept(*this);
    std::unique_ptr<const CExpression> right = std::move(childExpression);

    const CEseqExpression* leftEseq = dynamic_cast<const CEseqExpression*>(left.get());
    const CEseqExpression* rightEseq = dynamic_cast<const CEseqExpression*>(right.get());

    if (leftEseq == nullptr && rightEseq == nullptr) {
        childExpression = EMOVE_UNIQ(new CBinopExpression(
                std::move(left),
                std::move(right),
                expression.getOperation()
        ));

        return;
    }

    if (leftEseq == nullptr && rightEseq != nullptr) {
        childExpression = std::move(processRightEseqInCBinop(&expression, left.get(), rightEseq));

        return;
    }

    if (leftEseq != nullptr && rightEseq == nullptr) {
        childExpression = EMOVE_UNIQ(new CEseqExpression(
                std::move(leftEseq->getStatement()->Copy()),
                EMOVE_UNIQ(new CBinopExpression(
                        std::move(leftEseq->getExpression()->Copy()),
                        std::move(right),
                        expression.getOperation()
                ))
        ));


        return;
    }

    if (leftEseq != nullptr && rightEseq != nullptr) {
        childExpression = EMOVE_UNIQ(new CEseqExpression(
                std::move(leftEseq->getStatement()->Copy()),
                std::move(processRightEseqInCBinop(&expression, leftEseq->getExpression(), rightEseq))
        ));

        return;
    }
}

std::unique_ptr<const IRT::CExpression> IRT::CEseqFloatVisitor::processRightEseqInCBinop(
        const IRT::CBinopExpression *binop,
        const IRT::CExpression *left, const IRT::CEseqExpression *rightEseq) {

    if (isExpCommuteWithStm(left, rightEseq->getStatement())) {
        return EMOVE_UNIQ(new CEseqExpression(
                std::move(rightEseq->getStatement()->Copy()),
                EMOVE_UNIQ(new CBinopExpression(
                        std::move(left->Copy()),
                        std::move(rightEseq->getExpression()->Copy()),
                        binop->getOperation()
                ))
        ));
    } else {
        CTemp temp;
        return EMOVE_UNIQ(new CEseqExpression(
                SMOVE_UNIQ(new CSeqStatement(
                    SMOVE_UNIQ(new CMoveStatement(
                        EMOVE_UNIQ(new CTempExpression(temp)),
                        std::move(left->Copy())
                    )),
                    std::move(rightEseq->getStatement()->Copy())
                )),
                EMOVE_UNIQ(new CBinopExpression(
                        EMOVE_UNIQ(new CMemExpression( EMOVE_UNIQ(new CTempExpression(temp)))),
                        std::move(rightEseq->getExpression()->Copy()),
                        binop->getOperation()
                ))
        ));
    }
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CConstExpression &expression) {
    childExpression = std::move(expression.Copy());
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CTempExpression &expression) {
    childExpression = std::move(expression.Copy());
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CNameExpression &expression) {
    childExpression = std::move(expression.Copy());
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CCallExpression &expression) {
    expression.getArguments()->Accept(*this);
    std::unique_ptr<const CExpressionList> args = std::move(childExpressionList);

    if (args->getExpressions().size() == 0) {
        childExpression = EMOVE_UNIQ(new CCallExpression(
                std::move(expression.getFunction()->CopyCast()),
                std::move(args)
        ));

        return;
    }

    std::vector<std::unique_ptr<const CStatement>> helpStatements;

    CExpressionList* tempExpressionList = new CExpressionList();

    for (int i = 0; i < args->getExpressions().size(); ++i) {
        processCallArgument(args->getExpressions()[i].get(), tempExpressionList, helpStatements);
    }

    std::unique_ptr<const CStatement> rightStatement = std::move(helpStatements.back());
    helpStatements.pop_back();
    for (int i = 0; i < helpStatements.size(); ++i) {
        rightStatement = SMOVE_UNIQ(new CSeqStatement(
                std::move(helpStatements[i]),
                std::move(rightStatement)
        ));
    }

    childExpression = EMOVE_UNIQ(new CEseqExpression(
            std::move(rightStatement),
            EMOVE_UNIQ(new CCallExpression(
                    std::move(expression.getFunction()->CopyCast()),
                    std::move(std::unique_ptr<const CExpressionList>(tempExpressionList))
            ))
    ));
}

void IRT::CEseqFloatVisitor::processCallArgument(
        const IRT::CExpression *argExp,
        IRT::CExpressionList *tempExpressionList,
        std::vector<std::unique_ptr<const IRT::CStatement>> &helpStatements) {

    const CEseqExpression* argEseq = CAST_TO_ESEQ(argExp);

    if (argEseq != nullptr) {
        helpStatements.push_back(std::move(argEseq->getStatement()->Copy()));
    }

    CTemp argTemp;
    tempExpressionList->Add(new CTempExpression(argTemp));

    std::unique_ptr<const CExpression> source;
    if (argEseq != nullptr) {
        source = std::move(argEseq->getExpression()->Copy());
    } else {
        source = std::move(argExp->Copy());
    }

    helpStatements.push_back(SMOVE_UNIQ(new CMoveStatement(
            EMOVE_UNIQ(EMOVE_UNIQ(new CTempExpression(argTemp))),
            std::move(source)
    )));
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CMemExpression &expression) {
    expression.getAddress()->Accept(*this);

    const CEseqExpression* eseq = CAST_TO_ESEQ(childExpression.get());
    if (eseq == nullptr) {
        childExpression = EMOVE_UNIQ(new CMemExpression(
                std::move(childExpression)
        ));
    } else {
        childExpression = EMOVE_UNIQ(new CEseqExpression(
                std::move(eseq->getStatement()->Copy()),
                EMOVE_UNIQ(new CMemExpression(
                        std::move(eseq->getExpression()->Copy())
                ))
        ));
    }
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CExpressionList &expression) {
    CExpressionList* newList = new CExpressionList();
    for (int i = 0; i < expression.getExpressions().size(); ++i) {
        expression.getExpressions()[i]->Accept(*this);
        newList->Add(std::move(childExpression));
    }

    childExpressionList = std::move(std::unique_ptr<const CExpressionList>(newList));
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CMoveStatement &statement) {
    statement.Target()->Accept(*this);
    std::unique_ptr<const CExpression> target = std::move(childExpression);

    statement.Source()->Accept(*this);
    std::unique_ptr<const CExpression> source = std::move(childExpression);

    const CEseqExpression* targetEseq = dynamic_cast<const CEseqExpression*>(target.get());
    const CEseqExpression* sourceEseq = dynamic_cast<const CEseqExpression*>(source.get());

    if (targetEseq == nullptr && sourceEseq == nullptr) {
        childStatement = SMOVE_UNIQ(new CMoveStatement(
                std::move(target),
                std::move(source)
        ));

        return;
    }

    if (targetEseq == nullptr && sourceEseq != nullptr) {
        childStatement = std::move(processSourceEseqInCMove(target.get(), sourceEseq));

        return;
    }

    if (targetEseq != nullptr && sourceEseq == nullptr) {
        childStatement = SMOVE_UNIQ(new CSeqStatement(
                std::move(targetEseq->getStatement()->Copy()),
                SMOVE_UNIQ(new CMoveStatement(
                        std::move(targetEseq->getExpression()->Copy()),
                        std::move(source)
                ))
        ));

        return;
    }

    if (targetEseq != nullptr && sourceEseq != nullptr) {
        childStatement = SMOVE_UNIQ(new CSeqStatement(
                std::move(targetEseq->getStatement()->Copy()),
                std::move(processSourceEseqInCMove(target.get(), sourceEseq))
        ));

        return;
    }
}

std::unique_ptr<const IRT::CStatement> IRT::CEseqFloatVisitor::processSourceEseqInCMove(
        const IRT::CExpression *target, const IRT::CEseqExpression *sourceEseq) {

    const CEseqExpression* eseq = dynamic_cast<const CEseqExpression*>(sourceEseq->getExpression());
    assert(eseq == nullptr);

    if (isExpCommuteWithStm(target, sourceEseq->getStatement())) {
        return SMOVE_UNIQ(new CSeqStatement(
                std::move(sourceEseq->getStatement()->Copy()),
                SMOVE_UNIQ(new CMoveStatement(
                        std::move(target->Copy()),
                        std::move(sourceEseq->getExpression()->Copy())
                ))
        ));
    } else {

        const CMemExpression* memTarget = dynamic_cast<const CMemExpression*>(target);
        const CTempExpression* tempTarget = dynamic_cast<const CTempExpression*>(target);

        assert(memTarget != nullptr || tempTarget != nullptr);

        if (memTarget != nullptr) {
            CTemp temp;

            return SMOVE_UNIQ(new CSeqStatement(
                    SMOVE_UNIQ(new CMoveStatement(
                            EMOVE_UNIQ(new CTempExpression(temp)),
                            std::move(memTarget->getAddress()->Copy())
                    )),
                    SMOVE_UNIQ(new CSeqStatement(
                            std::move(sourceEseq->getStatement()->Copy()),
                            SMOVE_UNIQ(new CMoveStatement(
                                    EMOVE_UNIQ(new CMemExpression(EMOVE_UNIQ(new CTempExpression(temp)))),
                                    std::move(sourceEseq->getExpression()->Copy())
                            ))
                    ))
            ));
        }

        if (tempTarget != nullptr) {
            return SMOVE_UNIQ(new CSeqStatement(
                            std::move(sourceEseq->getStatement()->Copy()),
                            SMOVE_UNIQ(new CMoveStatement(
                                    EMOVE_UNIQ(tempTarget->Copy()),
                                    std::move(sourceEseq->getExpression()->Copy())
                            ))
            ));
        }
    }
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CExpStatement &statement) {
    statement.Expression()->Accept(*this);
    const CEseqExpression* eseq = CAST_TO_ESEQ(childExpression.get());
    if (eseq == nullptr) {
        childStatement = SMOVE_UNIQ(new CExpStatement(std::move(childExpression)));
    } else {
        childStatement = SMOVE_UNIQ(new CSeqStatement(
                std::move(eseq->getStatement()->Copy()),
                std::move(SMOVE_UNIQ(new CExpStatement(std::move(eseq->getExpression()->Copy()))))
        ));
    }
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CLabelStatement &statement) {
    childStatement = std::move(statement.Copy());
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CJumpStatement &statement) {
    childStatement = std::move(statement.Copy());
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CJumpConditionalStatement &statement) {
    statement.LeftOperand()->Accept(*this);
    std::unique_ptr<const CExpression> left = std::move(childExpression);

    statement.RightOperand()->Accept(*this);
    std::unique_ptr<const CExpression> right = std::move(childExpression);

    const CEseqExpression* leftEseq = CAST_TO_ESEQ(left.get());
    const CEseqExpression* rightEseq = CAST_TO_ESEQ(right.get());

    if (leftEseq == nullptr && rightEseq == nullptr) {
        childStatement = SMOVE_UNIQ(new CJumpConditionalStatement(
                statement.Operation(),
                std::move(left),
                std::move(right),
                std::move(statement.TrueLabel()->CastCopy()),
                std::move(statement.FalseLabel()->CastCopy())
        ));

        return;
    }

    if (leftEseq == nullptr && rightEseq != nullptr) {
        childStatement = std::move(processRightEseqInCJump(&statement, left.get(), rightEseq));
        return;
    }

    if (leftEseq != nullptr && rightEseq == nullptr) {
        childStatement = SMOVE_UNIQ(new CSeqStatement(
                std::move(leftEseq->getStatement()->Copy()),
                SMOVE_UNIQ(new CJumpConditionalStatement(
                        statement.Operation(),
                        std::move(leftEseq->getExpression()->Copy()),
                        std::move(right),
                        std::move(statement.TrueLabel()->CastCopy()),
                        std::move(statement.FalseLabel()->CastCopy())
                ))
        ));
        return;
    }

    if (leftEseq != nullptr && rightEseq != nullptr) {
        childStatement = SMOVE_UNIQ(new CSeqStatement(
                std::move(leftEseq->getStatement()->Copy()),
                std::move(processRightEseqInCJump(&statement, leftEseq->getExpression(), rightEseq))
        ));

        return;
    }
}

std::unique_ptr<const IRT::CStatement> IRT::CEseqFloatVisitor::processRightEseqInCJump(
        const IRT::CJumpConditionalStatement *cjump,
        const IRT::CExpression *left, const IRT::CEseqExpression *rightEseq) {

    if (isExpCommuteWithStm(left, rightEseq->getStatement())) {
        return SMOVE_UNIQ(new CSeqStatement(
                std::move(rightEseq->getStatement()->Copy()),
                SMOVE_UNIQ(new CJumpConditionalStatement(
                        cjump->Operation(),
                        std::move(left->Copy()),
                        std::move(rightEseq->getExpression()->Copy()),
                        std::move(cjump->TrueLabel()->CastCopy()),
                        std::move(cjump->FalseLabel()->CastCopy())
                ))
        ));
    } else {
        CTemp temp;
        return SMOVE_UNIQ(new CSeqStatement(
                SMOVE_UNIQ(new CMoveStatement(
                        EMOVE_UNIQ(new CTempExpression(temp)),
                        std::move(left->Copy())
                )),
                SMOVE_UNIQ(new CSeqStatement(
                        std::move(rightEseq->getStatement()->Copy()),
                        SMOVE_UNIQ(new CJumpConditionalStatement(
                                cjump->Operation(),
                                EMOVE_UNIQ(new CMemExpression(EMOVE_UNIQ(new CTempExpression(temp)))),
                                std::move(rightEseq->getExpression()->Copy()),
                                std::move(cjump->TrueLabel()->CastCopy()),
                                std::move(cjump->FalseLabel()->CastCopy())
                        ))
                ))
        ));
    }
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CSeqStatement &statement) {
    statement.LeftStatement()->Accept(*this);
    std::unique_ptr<const CStatement> left = std::move(childStatement);

    statement.RightStatement()->Accept(*this);
    std::unique_ptr<const CStatement> right = std::move(childStatement);

    childStatement = SMOVE_UNIQ(new CSeqStatement(
            std::move(left),
            std::move(right)
    ));
}

void IRT::CEseqFloatVisitor::Visit(const IRT::CStatementList &statement) {
    assert(false);
}

std::unique_ptr<const IRT::CStatement> IRT::CEseqFloatVisitor::getResultTree() {
    return std::move(childStatement);
}


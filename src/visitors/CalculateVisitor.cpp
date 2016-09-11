#pragma once

#include <iostream>

#include "IVisitor.h"
#include "IVisitorResult.h"
#include "CalculateResults.h"

#include "CPrintStm.h"
#include "CCompoundStm.h"
#include "COpExp.h"
#include "CNumExp"
#include "CAssignStm.h"
#include "CIdExp.h"


IVisitorResult CCalculateVisitor::Visit(CPrintStm *stm) {
	CalculateResult result = (CalculateResult) stm->expression->Accept(this);

	switch (result.getType) {
		case IntResulType:
			int value = ((CalculateIntResult) result).getValue();

			std::cout <<  << '\n';

			return CalculateNoneResult();
		case NoneResultType:
			return CalculateErrorResult();
		case ErrorResultType:
			return CalculateErrorResult();
	}
}

IVisitorResult CCalculateVisitor::Visit(CCompoundStm *stm) {
	CalculateResult leftResult = (CalculateResult) stm->leftStatement->Accept(this);
	CalculateResult rightResult = (CalculateResult) stm->rightStatement->Accept(this);

	if (leftResult.getType() == ErrorResultType || rightOperand.getType() == ErrorResultType) {
		return CalculateErrorResult();
	} else {
		return CalculateNoneResult();
	}
}

IVisitorResult CCalculateVisitor::Visit(COpExp *exp) {
	CalculateResult leftResult = (CalculateResult) exp->leftOperand->Accept(this);
	CalculateResult rightResult = (CalculateResult) exp->rightOperand->Accept(this);

	if (leftResult.getType() == IntResultType && rightOperand.getType() == IntResultType) {
		int leftValue = ((CalculateIntResult) leftResult).getValue();
		int rightValue = ((CalculateIntResult) rightResult).getValue();

		switch (exp->operation) {
			case PLUS:
				return CalculateIntResult(leftValue + rightValue);
			case MINUS:
				return CalculateIntResult(leftValue - rightValue);
			case MULTIPLY:
				return CalculateIntResult(leftValue * rightValue);
			case DIVISE:
				if (rightValue == 0) {
					return CalculateErrorResult();
				} else {
					return CalculateIntResult(leftValue / rightValue);
				}
		}
	} else {
		return CalculateErrorResult();
	}
}

IVisitorResult CCalculateVisitor::Visit(CNumExp *exp) {
	return CalculateIntResult(exp->number);
}

IVisitorResult CCalculateVisitor::Visit(CIdExp *exp) {
	return CalculateIntResult(*(exp->number));
}

IVisitorResult CCalculateVisitor::Visit(CAssignStm *exp) {
	CalculateResult result = (CalculateResult) exp->rightExpression->Accept(this);

	switch (result.getType) {
		case IntResulType:
			*(exp->leftExpression->number) = ((CalculateIntResult) result).getValue();
			return CalculateNoneResult();
		case NoneResultType:
			return CalculateErrorResult();
		case ErrorResultType:
			return CalculateErrorResult();
	}
}

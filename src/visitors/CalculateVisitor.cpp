#include <iostream>

#include "IVisitor.h"
#include "IVisitorResult.h"
#include "CalculateResults.h"
#include "CalculateVisitor.h"

#include "../nodes/statements/CPrintStm.h"
#include "../nodes/statements/CCompoundStm.h"
#include "../nodes/statements/CAssignStm.h"
#include "../nodes/expressions/COpExp.h"
#include "../nodes/expressions/CNumExp.h"
#include "../nodes/expressions/CIdExp.h"


IVisitorResult* CCalculateVisitor::Visit(CPrintStm *stm) {
	CalculateResult* result = reinterpret_cast<CalculateResult*>(stm->expression->Accept(this));

	switch (result->getType()) {
		case INT_RESULT_TYPE: {
				int value = (reinterpret_cast<CalculateIntResult*>(result))->getValue();

				std::cout << value << '\n';

				return new CalculateNoneResult();
			}
		case NONE_RESULT_TYPE:
			return new CalculateErrorResult();
		case ERROR_RESULT_TYPE:
			return new CalculateErrorResult();
	}
}

IVisitorResult* CCalculateVisitor::Visit(CCompoundStm *stm) {
	CalculateResult* leftResult = reinterpret_cast<CalculateResult*>(stm->leftStatement->Accept(this));
	CalculateResult* rightResult = reinterpret_cast<CalculateResult*>(stm->rightStatement->Accept(this));

	if (leftResult->getType() == ERROR_RESULT_TYPE || rightResult->getType() == ERROR_RESULT_TYPE) {
		return new CalculateErrorResult();
	} else {
		return new CalculateNoneResult();
	}
}

IVisitorResult* CCalculateVisitor::Visit(CSimpleStm *stm) {
	CalculateResult* result = reinterpret_cast<CalculateResult*>(stm->statement->Accept(this));

	if (result->getType() == ERROR_RESULT_TYPE) {
		return new CalculateErrorResult();
	} else {
		return new CalculateNoneResult();
	}
}

IVisitorResult* CCalculateVisitor::Visit(COpExp *exp) {
	CalculateResult* leftResult = reinterpret_cast<CalculateResult*>(exp->leftOperand->Accept(this));
	CalculateResult* rightResult = reinterpret_cast<CalculateResult*>(exp->rightOperand->Accept(this));

	if (leftResult->getType() == INT_RESULT_TYPE && rightResult->getType() == INT_RESULT_TYPE) {
		int leftValue = (reinterpret_cast<CalculateIntResult*>(leftResult))->getValue();
		int rightValue = (reinterpret_cast<CalculateIntResult*>(rightResult))->getValue();

		switch (exp->operation) {
			case PLUS:
				return new CalculateIntResult(leftValue + rightValue);
			case MINUS:
				return new CalculateIntResult(leftValue - rightValue);
			case MULTIPLY:
				return new CalculateIntResult(leftValue * rightValue);
			case DIVISE:
				if (rightValue == 0) {
					return new CalculateErrorResult();
				} else {
					return new CalculateIntResult(leftValue / rightValue);
				}
		}
	} else {
		return new CalculateErrorResult();
	}
}

IVisitorResult* CCalculateVisitor::Visit(CNumExp *exp) {
	return new CalculateIntResult(exp->number);
}

IVisitorResult* CCalculateVisitor::Visit(CIdExp *exp) {
	return new CalculateIntResult(*(exp->address));
}

IVisitorResult* CCalculateVisitor::Visit(CAssignStm *exp) {
	CalculateResult* result = reinterpret_cast<CalculateResult*>(exp->rightExpression->Accept(this));

	switch (result->getType()) {
		case INT_RESULT_TYPE: {
				*(exp->leftExpression->address) = (reinterpret_cast<CalculateIntResult*>(result))->getValue();
				return new CalculateNoneResult();
			}
		case NONE_RESULT_TYPE:
			return new CalculateErrorResult();
		case ERROR_RESULT_TYPE:
			return new CalculateErrorResult();
	}
}

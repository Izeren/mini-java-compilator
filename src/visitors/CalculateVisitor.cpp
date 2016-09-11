#pragma once

#include "IVisitor.h"
#include "IVisitorResult.h"
#include "CalculateResults.h"

#include "CPrintStm.h"
#include "CCompoundStm.h"
#include "COpExp.h"
#include "CNumExp"

class CCalculateVisitor : public IVisitor {
public:
	IVisitorResult Visit(CPrintStm *stm) {

	};

	IVisitorResult Visit(CCompoundStm *stm) {
	};

	IVisitorResult Visit(COpExp *exp) {
		CalculateResult leftResult = (CalculateResult) exp->leftOperand->Accept(this);
		CalculateResult rightResult = (CalculateResult) exp->rightOperand->Accept(this);

		if (leftResult.getType() == IntResultType && rightOperand.getType() == IntResultType) {

		} else {
			return CalculateErrorResult(0);
		}
	};

	IVisitorResult Visit(CNumExp *exp) {
		return CalculateIntResult(exp->number);
	};
}

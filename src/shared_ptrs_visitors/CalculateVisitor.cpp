#include <iostream>

#include "IVisitor.h"
#include "CalculateVisitor.h"

void CCalculateVisitor::Visit(CPrintStm &stm) {
	if (wasError) {
		return;
	}

	stm.expression.get()->Accept(*this);

	if (wasError) {
		return;
	}

	if (!this->isChildResultInteger) {
		this->wasError = true;
		return;
	}

	std::cout << this->childResult << '\n';
	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CCompoundStm &stm) {
	if (wasError) {
		return;
	}

	stm.leftStatement.get()->Accept(*this);
	stm.rightStatement.get()->Accept(*this);

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CSimpleStm &stm) {
	if (wasError) {
		return;
	}

	stm.statement.get()->Accept(*this);

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(COpExp &exp) {
	if (wasError) {
		return;
	}

	int leftResult;
	int rightResult;

	exp.leftOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	leftResult = this->childResult;

	exp.rightOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	rightResult = this->childResult;

	if (wasError) {
		return;
	}


	this->isChildResultInteger = true;
	switch (exp.operation) {
	case PLUS:
		this->childResult = leftResult + rightResult;
		break;
	case MINUS:
		this->childResult = leftResult - rightResult;
		break;
	case MULTIPLY:
		this->childResult = leftResult * rightResult;
		break;
		//case DIVISE:
		//	if (rightResult == 0) {
		//		this->wasError = true;
		//		break;
		//	} else {
		//		this->childResult = leftResult / rightResult;
		//		break;
		//	}
	}
}

void CCalculateVisitor::Visit(CNumExp &exp) {
	if (wasError) {
		return;
	}

	this->childResult = exp.number;
	this->isChildResultInteger = true;
}

void CCalculateVisitor::Visit(CIdExp &exp) {
	if (wasError) {
		return;
	}

	this->childResult = *(exp.address);
	this->isChildResultInteger = true;
}

//
void CCalculateVisitor::Visit(CLogExp &exp) {
	if (wasError) {
		return;
	}

	this->childResult = exp.variable;
	this->isChildResultInteger = true;
}

void CCalculateVisitor::Visit(CLogOpExp &exp) {
	if (wasError) {
		return;
	}

	int leftResult;
	int rightResult;

	exp.leftOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	leftResult = this->childResult;

	exp.rightOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	rightResult = this->childResult;

	if (wasError) {
		return;
	}

	this->isChildResultInteger = true;
	switch (exp.operation) {
	case AND:
		this->childResult = (leftResult && rightResult);
		break;
	case OR:
		this->childResult = (leftResult || rightResult);
		break;
	}
}

void CCalculateVisitor::Visit(CCompExp &exp) {
	if (wasError) {
		return;
	}

	int leftResult;
	int rightResult;

	exp.leftOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	leftResult = this->childResult;

	exp.rightOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	rightResult = this->childResult;

	if (wasError) {
		return;
	}

	this->isChildResultInteger = true;
	switch (exp.operation) {
	case GREATER:
		this->childResult = (leftResult > rightResult);
		break;
	case GREATER_OR_EQUAL:
		this->childResult = (leftResult >= rightResult);
		break;
	case LESS:
		this->childResult = (leftResult < rightResult);
		break;
	case LESS_OR_EQUAL:
		this->childResult = (leftResult <= rightResult);
		break;
	}
}

void CCalculateVisitor::Visit(CUnarMinusExp &exp) {
	if (wasError) {
		return;
	}

	int rightResult;

	exp.rightOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	rightResult = this->childResult;

	this->childResult = -rightResult;
}

void CCalculateVisitor::Visit(CIdPtrExp &exp) {
	if (wasError) {
		return;
	}

	this->childResult = *(exp.address);
	this->isChildResultInteger = true;
}

void CCalculateVisitor::Visit(CAssignStm &stm) {
	if (wasError) {
		return;
	}

	stm.rightExpression.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	if (wasError) {
		return;
	}

	int rightResult = this->childResult;

	*(stm.leftExpression.get()->address) = rightResult;

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CIfStm &stm) {
	if (wasError) {
		return;
	}

	stm.conditionExpression.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	if (wasError) {
		return;
	}

	if (childResult) {
		stm.positiveStatement.get()->Accept(*this);
	}
	else {
		stm.negativeStatement.get()->Accept(*this);
	}

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CWhileStm &stm) {
	if (wasError) {
		return;
	}

	stm.conditionExpression.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	if (wasError) {
		return;
	}

	while (childResult) {
		stm.statement.get()->Accept(*this);
		stm.conditionExpression.get()->Accept(*this);

		if (!this->isChildResultInteger) {
			wasError = true;
			return;
		}

		if (wasError) {
			return;
		}
	}

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CAssignSubscriptStm &stm) {
	if (wasError) {
		return;
	}

	stm.valueExpression.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	if (wasError) {
		return;
	}

	int valueResult = this->childResult;

	*(stm.idExpression.get()->addressc+ stm.offset.get().number) = valueResult;

	this->isChildResultInteger = false;
}

int CCalculateVisitor::GetResult() {
	return childResult;
}
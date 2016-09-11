#include "COpExp.h"

IVisitorResult COpExp::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

COpExp(IExpression *leftOperand = null, IExpression *rightOperand = null, TOperation operation = PLUS) {
	this->leftOperand = leftOperand;
	this->rightOperand = rightOperand;
	this->operation = operation;

}

~COpExp() {
	if (leftOperand != null) {
		delete leftOperand;
	}
	if (rightOperand != null) {
		delete rightOperand;
	}
}

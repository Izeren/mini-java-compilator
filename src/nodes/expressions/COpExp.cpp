#include "COpExp.h"

IVisitorResult COpExp::Accept(IVisitor *visitor) {
	return visitor->Visit(this);
}

COpExp::COpExp(IExpression *leftOperand, IExpression *rightOperand, TOperation operation) {
	this->leftOperand = leftOperand;
	this->rightOperand = rightOperand;
	this->operation = operation;

}

COpExp::~COpExp() {
	if (leftOperand) {
		delete leftOperand;
	}
	if (rightOperand) {
		delete rightOperand;
	}
}

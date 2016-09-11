#include "CAssignStm.h"

CAssignStm::CAssignStm(CIdExp *leftExpression, IExpression *rightExpression) {
	this->leftExpression = leftExpression;
	this->rightExpression = rightExpression;
}

CAssignStm::~CAssignStm() {
	if (leftExpression) {
		delete leftExpression;
	}
	if (rightExpression) {
		delete rightExpression;
	}
}

IVisitorResult CAssignStm::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

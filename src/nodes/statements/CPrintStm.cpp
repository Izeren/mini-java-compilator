#include "CPrintStm.h"

CPrintStm::CPrintStm(IExpression *expression) {
	this->expression = expression;
}

CPrintStm::~CPrintStm() {
	if (expression) {
		delete expression;
	}
}

IVisitorResult CPrintStm::Accept(IVisitor *visitor) {
	return visitor->Visit(this);
}

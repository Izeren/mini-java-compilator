#include "CNumExp.h"

CNumExp::CNumExp(int number) {
	this->number = number;
}

IVisitorResult* CNumExp::Accept(IVisitor *visitor) {
	return visitor->Visit(this);
}

CNumExp::~CNumExp() {}
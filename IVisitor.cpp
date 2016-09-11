#include "IVisitor.h"

void IVisitor::Visit(CPrintStm *visitor) {
	visitor->Accept(this);
}

void IVisitor::Visit(CCompoundStm *) {
	visitor->Accept(this);
}

void IVisitor::Visit(COpExp *) {
	visitor->Accept(this);
}

void IVisitor::Visit(CNumExp *) {
	visitor->Accept(this);
}
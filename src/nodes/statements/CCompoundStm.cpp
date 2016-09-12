#include "CCompoundStm.h"

CCompoundStm::CCompoundStm(IStatement *leftStatement, IStatement *rightStatement) {
	this->leftStatement = leftStatement;
	this->rightStatement = rightStatement;
}

CCompoundStm::~CCompoundStm() {
	if (leftStatement) {
		delete leftStatement;
	}
	if (rightStatement) {
		delete rightStatement;
	}
}

IVisitorResult CCompoundStm::Accept(IVisitor *visitor) {
	return visitor->Visit(this);
}

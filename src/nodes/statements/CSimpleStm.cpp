#include "CSimpleStm.h"

CSimpleStm::CSimpleStm(IStatement *statement) {
	this->statement = statement;
}

CSimpleStm::~CSimpleStm() {
	if (statement) {
		delete statement;
	}
}

IVisitorResult* CSimpleStm::Accept(IVisitor *visitor) {
	return visitor->Visit(this);
}

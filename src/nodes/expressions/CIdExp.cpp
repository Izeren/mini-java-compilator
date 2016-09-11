#include "CIdExp.h"

CIdExp::CIdExp(std::string name) {
	this->name = name;
}

IVisitorResult CIdExp::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

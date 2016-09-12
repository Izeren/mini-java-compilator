#include "CIdExp.h"

CIdExp::CIdExp(std::string name, int *address) {
	this->name = name;
	this->address = address;
}

IVisitorResult CIdExp::Accept(IVisitor *visitor) {
	return visitor->Visit(this);
}

CIdExp::~CIdExp() {
	if (address) {
		delete address;
	}
}

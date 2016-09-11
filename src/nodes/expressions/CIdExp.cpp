#include "CIdExp.h"

CIdExp::CIdExp(std::string name, int *address) {
	this->name = name;
	this->address = address;
}

IVisitorResult CIdExp::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

~CIdExp() {
	if (address != 0) {
		delete address;
	}
}

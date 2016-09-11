#include "CIdExp.h"

IVisitorResult CIdExp::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

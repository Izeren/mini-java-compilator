#include "COpExp.h"

IVisitorResult COpExp::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

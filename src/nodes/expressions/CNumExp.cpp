#include "CNumExp.h"

IVisitorResult CNumExp::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

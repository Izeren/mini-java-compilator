#include "CPrintStm.h"

IVisitorResult CPrintStm::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

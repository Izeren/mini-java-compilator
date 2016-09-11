#include "CCompoundStm.h"

IVisitorResult CCompoundStm::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

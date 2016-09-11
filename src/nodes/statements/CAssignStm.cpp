#include "CAssignStm.h"

IVisitorResult CAssignStm::Accept(IVisitor *visitor) {
	return visitor->visit(this);
}

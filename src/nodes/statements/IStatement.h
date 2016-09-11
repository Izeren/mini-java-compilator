#pragma once

#include "../INode.h"
#include "../../IVisitorResult.h"
#include "../../IVisitor.h"

class IStatement : public INode {
public:
	virtual IVisitorResult Acccept(IVisitor *visitor) = 0;
};
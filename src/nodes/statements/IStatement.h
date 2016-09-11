#pragma once

#include "../INode.h"
#include "../../visitors/IVisitorResult.h"
#include "../../visitors/IVisitor.h"

class IStatement : public INode {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) = 0;
};
#pragma once

#include "../INode.h"
#include "../../visitors/IVisitorResult.h"
#include "../../visitors/IVisitor.h"

class IExpression : public INode {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) = 0;
	virtual ~IVisitorResult();

};
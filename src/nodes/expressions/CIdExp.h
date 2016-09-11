#pragma once

#include "IExpression.h"

class CNumExp : public IExpression {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) override;
	
	int *number;
};
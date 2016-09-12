#pragma once

#include "IExpression.h"

class CNumExp : public IExpression {
public:
	CNumExp(int number = 0);
	IVisitorResult* Accept(IVisitor *visitor) override;
	~CNumExp();
	int number;
};
#pragma once

#include "IExpression.h"

class CNumExp : public IExpression {
public:
	CNumExp(int number = 0);
	virtual IVisitorResult Accept(IVisitor *visitor) override;
	~CNumExp();

private:
	int number;
};
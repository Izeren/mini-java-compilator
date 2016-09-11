#pragma once

#include "IStatement.h"

class CPrintStm : public IStatement {
public:
	CPrintStm(IExpression *expression = 0);
	~CPrintStm();

	virtual IVisitorResult Accept(IVisitor *visitor) override;

	IExpression *expression;
}; 
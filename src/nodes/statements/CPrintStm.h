#pragma once

#include "IStatement.h"

class CPrintStm : public IStatement {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) override;

private:
	IExpression *expression;
}; 
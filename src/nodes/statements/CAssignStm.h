#pragma once

#include "IStatement.h"

class CAssignStm : public IStatement {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) override;

	IExpression *rightExpression;
	IExpression *leftExpression;
};
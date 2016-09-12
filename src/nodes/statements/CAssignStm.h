#pragma once

#include "IStatement.h"

class CAssignStm : public IStatement {
public:
	CAssignStm(CIdExp *leftExpression = 0, IExpression *rightExpression = 0);
	~CAssignStm();

	IVisitorResult Accept(IVisitor *visitor) override;

	IExpression *rightExpression;
	CIdExp *leftExpression;
};

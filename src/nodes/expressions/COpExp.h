#pragma once

#include "IExpression.h"

enum TOperation { PLUS, MINUS, MULTIPLY, DIVISE };

class COpExp : public IExpression {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) override;
	COpExp(IExpression *leftOperand = null, IExpression *rightOperand = null, TOperation operation = PLUS);
	~COpExp();

	IExpression *leftOperand;
	IExpression *rightOperand;
	TOperation operaton;
};
#pragma once

#include "IExpression.h"

enum TOperation { PLUS, MINUS, MULTIPLY, DIVISE };

class COpExp : public IExpression {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	TOperation operaton;
};
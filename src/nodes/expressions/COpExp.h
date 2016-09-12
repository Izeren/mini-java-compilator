#pragma once

#include "IExpression.h"

enum TOperation { PLUS, MINUS, MULTIPLY, DIVISE };

class COpExp : public IExpression {
public:
	IVisitorResult* Accept(IVisitor *visitor) override;
	COpExp(IExpression *leftOperand = nullptr, IExpression *rightOperand = nullptr, TOperation operation = PLUS);
	~COpExp();

	IExpression *leftOperand;
	IExpression *rightOperand;
	TOperation operation;
};

#pragma once

#include "INode.h"

class IExpression : public INode {};


class CIdExp : public IExpression {
public:
	void Accept(IVisitor &visitor) override;
	CIdExp();
	CIdExp(const std::string &name, int *address = 0);
	int *address;

	std::string name;
};


class CNumExp : public IExpression {
public:
	CNumExp(int number = 0);
	void Accept(IVisitor &visitor) override;
	int number;
};

enum TOperation { PLUS, MINUS, MULTIPLY, DIVISE };

class COpExp : public IExpression {
public:
	void Accept(IVisitor &visitor) override;
	COpExp();
	COpExp(
		std::shared_ptr<IExpression> leftOperand, 
		std::shared_ptr<IExpression> rightOperand, 
		TOperation operation = PLUS
	);

	std::shared_ptr<IExpression> leftOperand;
	std::shared_ptr<IExpression> rightOperand;
	TOperation operation;
};
#pragma once

#include "INode.h"
#include "../Utils.h"
#include <map>
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

class COpExp : public IExpression {
public:

	static std::map<enums::TOperation, std::string> stringOperations;

	void Accept(IVisitor &visitor) override;
	COpExp();
	COpExp(
		std::shared_ptr<IExpression> leftOperand, 
		std::shared_ptr<IExpression> rightOperand, 
		enums::TOperation operation = enums::TOperation::PLUS
	);

	std::shared_ptr<IExpression> leftOperand;
	std::shared_ptr<IExpression> rightOperand;
	enums::TOperation operation;
};
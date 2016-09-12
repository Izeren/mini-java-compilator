#pragma once

#include "IExpression.h"
#include <string>

class CIdExp : public IExpression {
public:
	IVisitorResult* Accept(IVisitor *visitor) override;
	CIdExp(std::string name = "a", int *address = 0);
	int *address;
	~CIdExp();

	std::string name;
};

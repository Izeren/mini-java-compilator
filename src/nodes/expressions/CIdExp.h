#pragma once

#include "IExpression.h"
#include <string>

class CIdExp : public IExpression {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) override;
	CIdExp(std::string name = "a", int *address);
	int *address;
	~CIdExp();

private:
	std::string name;
};

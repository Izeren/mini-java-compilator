#pragma once

#include "../INode.h"
#include "../expressions/IExpression.h"

class IStatement : public INode {
public:
	virtual ~IStatement() {}
};
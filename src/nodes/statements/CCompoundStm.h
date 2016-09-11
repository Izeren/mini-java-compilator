#pragma once

#include "IStatement.h"

class CCompoundStm : public IStatement {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) override;

	IStatement *leftStatement;
	IStatement *rightStatement;
};
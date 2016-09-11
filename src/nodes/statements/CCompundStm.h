#pragma once

#include "IStatement.h"

class CCompoundStm : public IStatement {
public:
	virtual IVisitorResult Accept(IVisitor *visitor) override;

private:
	IStatement *leftStatement;
	IStatement *rightStatement;
};
#pragma once

#include "IStatement.h"

class CCompoundStm : public IStatement {
public:
	CCompoundStm(IStatement *leftStatement = 0, IStatement *rightStatement = 0);
	~CCompoundStm();
	virtual IVisitorResult Accept(IVisitor *visitor) override;

	IStatement *leftStatement;
	IStatement *rightStatement;
};
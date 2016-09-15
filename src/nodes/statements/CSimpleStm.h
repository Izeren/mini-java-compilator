#pragma once

#include "IStatement.h"

class CSimpleStm : public IStatement {
public:
	CSimpleStm(IStatement *statement = 0);
	~CSimpleStm();
	IVisitorResult* Accept(IVisitor *visitor) override;

	IStatement *statement;
};
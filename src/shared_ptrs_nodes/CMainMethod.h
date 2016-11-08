#pragma once

#include "Statements.h"

class CMainMethod : public INode {
public:

	void Accept(IVisitor &visitor) override;
	CMainMethod();
	CMainMethod(CCompoundStm* _statementList);

	std::unique_ptr<CCompoundStm> statementList;

};
#pragma once

#include "Statements.h"
#include "CMainClass.h"

class CProgram : public INode {
public:

	void Accept(IVisitor &visitor) override;
	CProgram();
	CProgram(CMainClass *_class, CCompoundStm *_classList);

	std::unique_ptr<CClass> mainClass;
	std::unique_ptr<CCompoundStm> classList;

};
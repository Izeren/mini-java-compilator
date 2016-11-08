#pragma once

#include "Statements.h"
#include "CMainClass.h"

class CProgram : public INode {
public:

	void Accept(IVisitor &visitor) override;
	CProgram();
	CProgram(CMainClass* _class, CCLassList* _classList);

	std::unique_ptr<CMainClass> mainClass;
	std::unique_ptr<CCLassList> classList;

};
#pragma once

#include "Expressions.h"
#include "CMainMethod.h"


class CMainClass : public INode {
public:

	void Accept(IVisitor &visitor) override;
	CMainClass();
	CMainClass(CIdExp* _id, CMainMethod* _mainMethod);

	std::unique_ptr<CIdExp> id;
	std::unique_ptr<CMainMethod> mainMethod;

};
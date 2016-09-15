#pragma once

#include "IVisitor.h"
#include "IVisitorResult.h"
#include "../nodes/statements/CPrintStm.h"
#include "../nodes/statements/CCompoundStm.h"
#include "../nodes/statements/CAssignStm.h"
#include "../nodes/statements/CSimpleStm.h"
#include "../nodes/expressions/COpExp.h"
#include "../nodes/expressions/CNumExp.h"
#include "../nodes/expressions/CIdExp.h"

#include <string>

class CPrintVisitor : public IVisitor {
public:

	CPrintVisitor();

	IVisitorResult* Visit(CPrintStm *stm) override;
	IVisitorResult* Visit(CCompoundStm *stm) override;
	IVisitorResult* Visit(COpExp *exp) override;
	IVisitorResult* Visit(CNumExp *exp) override;
	IVisitorResult* Visit(CIdExp *exp) override;
	IVisitorResult* Visit(CAssignStm *exp) override;
	IVisitorResult* Visit(CSimpleStm *exp) override;

private:
	int lastVisited;
	std::string description;
};

#pragma once

#include <iostream>

#include "IVisitor.h"

#include "../nodes/statements/CPrintStm.h"
#include "../nodes/statements/CCompoundStm.h"
#include "../nodes/statements/CAssignStm.h"
#include "../nodes/statements/CSimpleStm.h"
#include "../nodes/expressions/COpExp.h"
#include "../nodes/expressions/CNumExp.h"
#include "../nodes/expressions/CIdExp.h"

class CCalculateVisitor : public IVisitor {
public:
	IVisitorResult* Visit(CPrintStm *stm) override;
	IVisitorResult* Visit(CCompoundStm *stm) override;
	IVisitorResult* Visit(COpExp *exp) override;
	IVisitorResult* Visit(CNumExp *exp) override;
	IVisitorResult* Visit(CIdExp *exp) override;
	IVisitorResult* Visit(CAssignStm *exp) override;
	IVisitorResult* Visit(CSimpleStm *exp) override;
};

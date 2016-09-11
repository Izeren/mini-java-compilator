#pragma once

#include "IVisitorResult.h"

#include "../nodes/statements/CPrintStm.h"
#include "../nodes/statements/CCompoundStm.h"
#include "../nodes/statements/CAssignStm.h"
#include "../nodes/expressions/COpExp.h"
#include "../nodes/expressions/CNumExp.h"
#include "../nodes/expressions/CIdExp.h"

class IVisitor {
public:
	virtual IVisitorResult Visit(CPrintStm *stm) = 0;
	virtual IVisitorResult Visit(CCompoundStm *stm) = 0;
	virtual IVisitorResult Visit(COpExp *exp) = 0;
	virtual IVisitorResult Visit(CNumExp *exp) = 0;
	virtual IVisitorResult Visit(CIdExp *exp) = 0;
	virtual IVisitorResult Visit(CAssignStm *exp) = 0;

};

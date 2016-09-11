#pragma once

#include "IVisitorResult.h"

#include "CPrintStm.h"
#include "CCompoundStm.h"
#include "COpExp.h"
#include "CNumExp"

class IVisitor {
public:
	virtual IVisitorResult Visit(CPrintStm *stm) = 0;
	virtual IVisitorResult Visit(CCompoundStm *stm) = 0;
	virtual IVisitorResult Visit(COpExp *exp) = 0;
	virtual IVisitorResult Visit(CNumExp *exp) = 0;
	virtual IVisitorResult Visit(CIdExp *exp) = 0;
	virtual IVisitorResult Visit(CAssignStm *exp) = 0;

};

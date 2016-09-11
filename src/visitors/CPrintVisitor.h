#pragma once

#include "IVisitor.h"
#include "IVisitorResult.h"

#include "CPrintStm.h"
#include "CCompoundStm.h"
#include "CAssignStm.h"
#include "COpExp.h"
#include "CNumExp.h"
#include "CIdExp.h"

class CPrintVisitor : public IVisitor {
public:
	IVisitorResult Visit(CPrintStm *stm) override;

	IVisitorResult Visit(CCompoundStm *stm) override;

	IVisitorResult Visit(COpExp *exp) override;

	IVisitorResult Visit(CNumExp *exp) override;

	IVisitorResult Visit(CIdExp *exp) override;

	IVisitorResult Visit(CAssignStm *exp) override;

private:
	int currentId;

};

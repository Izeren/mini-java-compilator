#pragma once

#include <iostream>
#include <map>
#include <memory>

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
	void Visit(CPrintStm *stm) override;
	void Visit(CCompoundStm *stm) override;
	void Visit(COpExp *exp) override;
	void Visit(CNumExp *exp) override;
	void Visit(CIdExp *exp) override;
	void Visit(CAssignStm *exp) override;
	void Visit(CSimpleStm *exp) override;

private:
	int childResult;

	bool isChildResultInteger;

	bool wasError = false;
};

#pragma once

#include <iostream>

#include "IVisitor.h"

class CCalculateVisitor : public IVisitor {
public:
	IVisitorResult Visit(CPrintStm *stm) override;
	IVisitorResult Visit(CCompoundStm *stm) override;
	IVisitorResult Visit(COpExp *exp) override;
	IVisitorResult Visit(CNumExp *exp) override;
	IVisitorResult Visit(CIdExp *exp) override;
	IVisitorResult Visit(CAssignStm *exp) override;
};

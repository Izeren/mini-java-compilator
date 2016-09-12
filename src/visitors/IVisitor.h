#pragma once

#include "IVisitorResult.h"

class CPrintStm;
class CCompoundStm;
class CAssignStm;
class COpExp;
class CNumExp;
class CIdExp; 

class IVisitor {
public:
	virtual IVisitorResult* Visit(CPrintStm *stm) = 0;
	virtual IVisitorResult* Visit(CCompoundStm *stm) = 0;
	virtual IVisitorResult* Visit(COpExp *exp) = 0;
	virtual IVisitorResult* Visit(CNumExp *exp) = 0;
	virtual IVisitorResult* Visit(CIdExp *exp) = 0;
	virtual IVisitorResult* Visit(CAssignStm *exp) = 0;

};

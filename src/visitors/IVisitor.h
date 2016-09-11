#pragma once

class IVisitor {

	virtual void Visit(CPrintStm *visitor) = 0;
	virtual void Visit(CCompoundStm *visitor) = 0;
	virtual void Visit(COpExp *visitor) = 0;
	virtual void Visit(CNumExp *visitor) = 0;

};
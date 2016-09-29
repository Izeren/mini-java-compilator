#pragma once

class CPrintStm;
class CCompoundStm;
class CAssignStm;
class COpExp;
class CNumExp;
class CIdExp; 
class CSimpleStm;

class IVisitor {
public:
	virtual void Visit(CPrintStm &stm) = 0;
	virtual void Visit(CCompoundStm &stm) = 0;
	virtual void Visit(COpExp &exp) = 0;
	virtual void Visit(CNumExp &exp) = 0;
	virtual void Visit(CIdExp &exp) = 0;
	virtual void Visit(CAssignStm &exp) = 0;
	virtual void Visit(CSimpleStm &exp) = 0;

};

#pragma once

class CPrintStm;
class CCompoundStm;
class COpExp;
class CNumExp;
class CIdExp;
class CIdPtrExp;
class CLogExp;
class CLogOpExp;
class CCompExp;
class CUnarMinusExp;
class CAssignStm;
class CSimpleStm;
class CIfStm;
class CWhileStm;
class CAssignSubscriptStm;

class IVisitor {
public:
	virtual void Visit(CPrintStm &stm) = 0;
	virtual void Visit(CCompoundStm &stm) = 0;
	virtual void Visit(COpExp &exp) = 0;
	virtual void Visit(CNumExp &exp) = 0;
	virtual void Visit(CIdExp &exp) = 0;
	virtual void Visit(CIdPtrExp &exp) = 0;
	virtual void Visit(CLogExp &exp) = 0;
	virtual void Visit(CLogOpExp &exp) = 0;
	virtual void Visit(CCompExp &exp) = 0;
	virtual void Visit(CUnarMinusExp &exp) = 0;
	virtual void Visit(CAssignStm &exp) = 0;
	virtual void Visit(CSimpleStm &exp) = 0;
	virtual void Visit(CIfStm &exp) = 0;
	virtual void Visit(CWhileStm &exp) = 0;
	virtual void Visit(CAssignSubscriptStm &exp) = 0;
};

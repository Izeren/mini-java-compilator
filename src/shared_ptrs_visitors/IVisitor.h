#pragma once

class CIdExp;
class CIdPtrExp;
class CNumExp;
class COpExp;
class CLogExp;
class CLogOpExp;
class CCompExp;
class CUnarMinusExp;
class CGetLengthExp;
class CGetFieldExp;
class CCallMethodExp;
class CExpList;
class CNegativeExpression;
class CNewArrayExpression;
class CGetFieldByThisExpression;
class CByIndexExpression;
class CNewIdentifier;
class CThisExpression;

class CAssignStm;
class CAssignSubscriptStm;
class CCompoundStm;
class CPrintStm;
class CIfStm;
class CWhileStm;

class CType;
class CField;
class CFieldList;
class CArgument;
class CArgumentList;
class CMethod;
class CMethodList;
class CClass;
class CClassList;
class CMainMethod;
class CMainClass;
class CProgram;

class IVisitor {
public:
	virtual void Visit(CIdExp &exp) = 0;
	virtual void Visit(CIdPtrExp &exp) = 0;
	virtual void Visit(CNumExp &exp) = 0;
	virtual void Visit(COpExp &exp) = 0;
	virtual void Visit(CLogExp &exp) = 0;
	virtual void Visit(CLogOpExp &exp) = 0;
	virtual void Visit(CCompExp &exp) = 0;
	virtual void Visit(CUnarMinusExp &exp) = 0;
	virtual void Visit(CGetLengthExp &exp) = 0;
	virtual void Visit(CGetFieldExp &exp) = 0;
	virtual void Visit(CCallMethodExp &exp) = 0;
	virtual void Visit(CExpList &exp) = 0;
	virtual void Visit(CNegativeExpression &exp) = 0;
	virtual void Visit(CNewArrayExpression &exp) = 0;
	virtual void Visit(CNewIdentifier &exp) = 0;
	virtual void Visit(CGetFieldByThisExpression &exp) = 0;
	virtual void Visit(CByIndexExpression &exp) = 0;
	virtual void Visit(CThisExpression &exp) = 0;

	virtual void Visit(CAssignStm &stm) = 0;
	virtual void Visit(CAssignSubscriptStm &stm) = 0;
	virtual void Visit(CCompoundStm &stm) = 0;
	virtual void Visit(CPrintStm &stm) = 0;
	virtual void Visit(CIfStm &stm) = 0;
	virtual void Visit(CWhileStm &stm) = 0;

	virtual void Visit(CType &stm) = 0;
	virtual void Visit(CField &stm) = 0;
	virtual void Visit(CFieldList &stm) = 0;
	virtual void Visit(CArgument &stm) = 0;
	virtual void Visit(CArgumentList &stm) = 0;
	virtual void Visit(CMethod &stm) = 0;
	virtual void Visit(CMethodList &stm) = 0;
	virtual void Visit(CClass &stm) = 0;
	virtual void Visit(CClassList &stm) = 0;
	virtual void Visit(CMainMethod &stm) = 0;
	virtual void Visit(CMainClass &stm) = 0;
	virtual void Visit(CProgram &stm) = 0;
};

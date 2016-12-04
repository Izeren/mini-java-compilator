#pragma once

#include "INode.h"
#include "../Utils.h"
#include <map>
#include <vector>


class IExpression : public PositionedNode {};

//CIdExp:
//-------------------------------------------------------------------------------------------------

class CIdExp : public IExpression {
public:
	void Accept(IVisitor &visitor) override;
	CIdExp(char *name, int *address = 0);
	int *address;

	std::string name;
};

//CIdPtrExp:
//-------------------------------------------------------------------------------------------------

class CIdPtrExp : public IExpression {
public:
	void Accept(IVisitor &visitor) override;
	CIdPtrExp();
	CIdPtrExp(const std::string &name, int *address = 0);
	int *address;

	std::string name;
};


//CNumExp:
//-------------------------------------------------------------------------------------------------

class CNumExp : public IExpression {
public:
	CNumExp(const char* number = "0");
	void Accept(IVisitor &visitor) override;
	int number;
};


//COpExp:
//-------------------------------------------------------------------------------------------------

class COpExp : public IExpression {
public:

	static std::map<enums::TOperation, std::string> stringOperations;

	void Accept(IVisitor &visitor) override;
	COpExp();
	COpExp(
		IExpression* leftOperand,
		IExpression* rightOperand,
		enums::TOperation operation = enums::TOperation::PLUS
	);

	std::unique_ptr<IExpression> leftOperand;
	std::unique_ptr<IExpression> rightOperand;
	enums::TOperation operation;
};

//CLogExp:
//-------------------------------------------------------------------------------------------------

class CLogExp : public IExpression {
public:
	CLogExp(bool variable = true);
	void Accept(IVisitor &visitor) override;
	bool variable;
};

//CLogOpExp:
//-------------------------------------------------------------------------------------------------

class CLogOpExp : public IExpression {
public:

	static std::map<enums::TLogicalOperation, std::string> stringOperations;

	void Accept(IVisitor &visitor) override;
	CLogOpExp();
	CLogOpExp(
		IExpression* leftOperand,
		IExpression* rightOperand,
		enums::TLogicalOperation operation
	);

	std::unique_ptr<IExpression> leftOperand;
	std::unique_ptr<IExpression> rightOperand;
	enums::TLogicalOperation operation;
};

//CCompExp:
//-------------------------------------------------------------------------------------------------

class CCompExp : public IExpression {
public:

	static std::map<enums::TCompareOperation, std::string> stringOperations;

	void Accept(IVisitor &visitor) override;
	CCompExp();
	CCompExp(
		IExpression* leftOperand,
		IExpression* rightOperand,
		enums::TCompareOperation operation = enums::TCompareOperation::GREATER
	);

	std::unique_ptr<IExpression> leftOperand;
	std::unique_ptr<IExpression> rightOperand;
	enums::TCompareOperation operation;
};


//CUnarMinusExp:
//-------------------------------------------------------------------------------------------------

class CUnarMinusExp : public IExpression {
public:
	CUnarMinusExp(IExpression* rightOperand);
	void Accept(IVisitor &visitor) override;
	std::unique_ptr<IExpression> rightOperand;
};

//CGetFieldExp:
//-------------------------------------------------------------------------------------------------

class CClass;
class CField;

class CGetFieldExp : public IExpression {
public: 
	CGetFieldExp(CClass* _classOwner, CField* _field);
	void Accept(IVisitor& visitor) override;
	std::unique_ptr<CClass> classOwner;
	std::unique_ptr<CField> field;
};


//CExpList:
//-------------------------------------------------------------------------------------------------

class CExpList : public IExpression {
public:
    CExpList();
    CExpList(IExpression* _exp);
	void Add(IExpression* _exp);
	void Accept(IVisitor &visitor) override;

    std::vector<std::unique_ptr<IExpression> > exps;
};

//CCallMethodExp:
//-------------------------------------------------------------------------------------------------
class CMethod;

class CCallMethodExp : public IExpression {
public: 
	CCallMethodExp(CClass* _classOwner, CIdExp* _methodName, CExpList* _args);
	void Accept(IVisitor& visitor) override;
	std::unique_ptr<CClass> classOwner;
	std::unique_ptr<CIdExp> methodName;
	std::unique_ptr<CExpList> args;
};

//CThisExpression:
//-------------------------------------------------------------------------------------------------

class CThisExpression : public IExpression {
public:
	CThisExpression();

	void Accept(IVisitor &visitor) override;
};

//CNegativeExpression:
//-------------------------------------------------------------------------------------------------

class CNegativeExpression : public IExpression {
public:
	CNegativeExpression(IExpression* expression);

	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IExpression> expression;
};

//CArrayExpression:
//-------------------------------------------------------------------------------------------------

class CArrayExpression : public IExpression {
public:
	CArrayExpression(IExpression* lengthExpression);

	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IExpression> lengthExpression;
};


//CGetLengthExp:
//-------------------------------------------------------------------------------------------------
class CGetLengthExp : public IExpression {
public: 
	CGetLengthExp(CArrayExpression* _array);
	void Accept(IVisitor& visitor) override;
	std::unique_ptr<CArrayExpression> array;
};


class CByIndexExpression : public IExpression {
public:
	CByIndexExpression(CArrayExpression* arrayExpression, IExpression* indexExpression);
	void Accept(IVisitor& visitor) override;
	std::unique_ptr<CArrayExpression> arrayExpression;
	std::unique_ptr<IExpression> indexExpression;
};

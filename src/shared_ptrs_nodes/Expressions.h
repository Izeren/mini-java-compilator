#pragma once

#include "INode.h"
#include "../Utils.h"
#include <map>
#include <vector>


class IExpression : public PositionedNode {
public:
	virtual void Accept(IVisitor &) = 0;
};

//CIdExp:
//-------------------------------------------------------------------------------------------------

class CIdExp : public IExpression {
public:
	void Accept(IVisitor &visitor) override;
	CIdExp(char *name);

	std::string name;
    bool isInstance = false;
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
	CCallMethodExp(IExpression* _objectExpression, CIdExp* _methodName, CExpList* _args);
	void Accept(IVisitor& visitor) override;

//	std::unique_ptr<CIdExp> objectName;
	std::unique_ptr<IExpression> objectExpression;
	std::unique_ptr<CIdExp> methodName;
	std::unique_ptr<CExpList> args;
};

//CThisExpression
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

//CNewArrayExpression:
//-------------------------------------------------------------------------------------------------

class CNewArrayExpression : public IExpression {
public:
	CNewArrayExpression(IExpression* lengthExpression);

	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IExpression> lengthExpression;
};

//CNewIdentifier:
//-------------------------------------------------------------------------------------------------
class CNewIdentifier : public IExpression {
public:
	CNewIdentifier( CIdExp* identifier );

	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CIdExp> identifier;
};


//CGetLengthExp:
//-------------------------------------------------------------------------------------------------
class CGetLengthExp : public IExpression {
public: 
	CGetLengthExp(IExpression* _array);
	void Accept(IVisitor& visitor) override;
	std::unique_ptr<IExpression> arrayIdentifier;
};


class CByIndexExpression : public IExpression {
public:
	CByIndexExpression(IExpression* arrayExpression, IExpression* indexExpression);
	void Accept(IVisitor& visitor) override;
	std::unique_ptr<IExpression> identifier;
	std::unique_ptr<IExpression> indexExpression;
};

#pragma once

#include "INode.h"
#include <unordered_map>
#include <map>


class IExpression : public INode {};

//CIdExp:
//-------------------------------------------------------------------------------------------------

class CIdExp : public IExpression {
public:
	void Accept(IVisitor &visitor) override;
	CIdExp();
	CIdExp(const std::string &name, int *address = 0);
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
	CNumExp(int number = 0);
	void Accept(IVisitor &visitor) override;
	int number;
};


//COpExp:
//-------------------------------------------------------------------------------------------------

enum TOperation { PLUS, MINUS, MULTIPLY, MOD };

class COpExp : public IExpression {
public:

	static std::map<TOperation, std::string> stringOperations;

	void Accept(IVisitor &visitor) override;
	COpExp();
	COpExp(
		IExpression* leftOperand,
		IExpression* rightOperand,
		TOperation operation = TOperation::PLUS
	);

	std::unique_ptr<IExpression> leftOperand;
	std::unique_ptr<IExpression> rightOperand;
	TOperation operation;
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

enum TLogicalOperation { AND, OR };

class CLogOpExp : public IExpression {
public:

	static std::map<TLogicalOperation, std::string> stringOperations;

	void Accept(IVisitor &visitor) override;
	CLogOpExp();
	CLogOpExp(
		IExpression* leftOperand,
		IExpression* rightOperand,
		TLogicalOperation operation = TLogicalOperation::AND
	);

	std::unique_ptr<IExpression> leftOperand;
	std::unique_ptr<IExpression> rightOperand;
	TLogicalOperation operation;
};

//CCompExp:
//-------------------------------------------------------------------------------------------------

enum TCompareOperation { GREATER, GREATER_OR_EQUAL, LESS, LESS_OR_EQUAL };

class CCompExp : public IExpression {
public:

	static std::map<TCompareOperation, std::string> stringOperations;

	void Accept(IVisitor &visitor) override;
	CCompExp();
	CCompExp(
		IExpression* leftOperand,
		IExpression* rightOperand,
		TCompareOperation operation = TCompareOperation::GREATER
	);

	std::unique_ptr<IExpression> leftOperand;
	std::unique_ptr<IExpression> rightOperand;
	TCompareOperation operation;
};


//CUnarMinusExp:
//-------------------------------------------------------------------------------------------------

class CUnarMinusExp : public IExpression {
public:
	CUnarMinusExp(IExpression* rightOperand);
	void Accept(IVisitor &visitor) override;
	std::unique_ptr<IExpression> rightOperand;
};

//CThisExpression:
//-------------------------------------------------------------------------------------------------

class CThisExpression : public IExpression {
public:
	CThisExpression();

	void Accept(IVisitor &visitor) override;
}

//CNegativeExpression:
//-------------------------------------------------------------------------------------------------

class CNegativeExpression : public IExpression {
public:
	CNegativeExpression(IExpression* expression);

	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IExpression> expression;
}

//CArrayExpression:
//-------------------------------------------------------------------------------------------------

class CArrayExpression : public IExpression {
public:
	CArrayExpression(IExpression* lengthExpression);

	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IExpression> lengthExpression;
}

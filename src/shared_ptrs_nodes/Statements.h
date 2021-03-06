#pragma once

#include "INode.h"
#include "Expressions.h"

class IStatement : public PositionedNode {};


//CAssignStm:
//-------------------------------------------------------------------------------------------------

class CAssignStm : public IStatement {
public:
	CAssignStm(CIdExp* leftExpression, IExpression* rightExpression);
	CAssignStm();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CIdExp> leftExpression;
	std::unique_ptr<IExpression> rightExpression;
};

//CAssignSubscriptStm:
//-------------------------------------------------------------------------------------------------

class CAssignSubscriptStm : public IStatement {
public:
	CAssignSubscriptStm(CIdExp* idExpression, IExpression* _index, IExpression* valueExpression);
	CAssignSubscriptStm();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<CIdExp> idExpression;
	std::unique_ptr<IExpression> indexExpression;
	std::unique_ptr<IExpression> valueExpression;
};


//CCompoundStm:
//-------------------------------------------------------------------------------------------------

class CCompoundStm : public IStatement {
public:
	CCompoundStm();
	CCompoundStm(IStatement* leftStatement, IStatement* rightStatement);
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IStatement> leftStatement;
	std::unique_ptr<IStatement> rightStatement;
};


//CPrintStm:
//-------------------------------------------------------------------------------------------------

class CPrintStm : public IStatement {
public:
	CPrintStm();
	CPrintStm(IExpression* expression);

	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IExpression> expression;
};


//CIfStm:
//-------------------------------------------------------------------------------------------------

class CIfStm : public IStatement {
public:
	CIfStm(
		IExpression* conditionExpression,
		IStatement* positiveStatement,
		IStatement* negativeStatement
	);
	CIfStm();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IExpression> conditionExpression;
	std::unique_ptr<IStatement> positiveStatement;
	std::unique_ptr<IStatement> negativeStatement;
};


//CWhileStm:
//-------------------------------------------------------------------------------------------------

class CWhileStm : public IStatement {
public:
	CWhileStm(
		IExpression* conditionExpression,
		IStatement* statement
	);
	CWhileStm();
	void Accept(IVisitor &visitor) override;

	std::unique_ptr<IExpression> conditionExpression;
	std::unique_ptr<IStatement> statement;
};
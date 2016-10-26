#pragma once

#include "INode.h"
#include "Expressions.h"

class IStatement : public INode {};


//CAssignStm:
//-------------------------------------------------------------------------------------------------

class CAssignStm : public IStatement {
public:
	CAssignStm(std::shared_ptr<CIdExp> leftExpression, std::shared_ptr<IExpression> rightExpression);
	CAssignStm();
	void Accept(IVisitor &visitor) override;

	std::shared_ptr<CIdExp> leftExpression;
	std::shared_ptr<IExpression> rightExpression;
};


//CCompoundStm:
//-------------------------------------------------------------------------------------------------

class CCompoundStm : public IStatement {
public:
	CCompoundStm();
	CCompoundStm(std::shared_ptr<IStatement> leftStatement, std::shared_ptr<IStatement> rightStatement);
	void Accept(IVisitor &visitor) override;

	std::shared_ptr<IStatement> leftStatement;
	std::shared_ptr<IStatement> rightStatement;
};


//CPrintStm:
//-------------------------------------------------------------------------------------------------

class CPrintStm : public IStatement {
public:
	CPrintStm();
	CPrintStm(std::shared_ptr<IExpression> expression);

	void Accept(IVisitor &visitor) override;

	std::shared_ptr<IExpression> expression;
};


//CSimpleStm:
//-------------------------------------------------------------------------------------------------

class CSimpleStm : public IStatement {
public:
	CSimpleStm();
	CSimpleStm(std::shared_ptr<IStatement> statement);
	void Accept(IVisitor &visitor) override;

	std::shared_ptr<IStatement> statement;
};


//CIfStm:
//-------------------------------------------------------------------------------------------------

class CIfStm : public IStatement {
public:
	CIfStm(
		std::shared_ptr<IExpression> conditionExpression,
		std::shared_ptr<IStatement> positiveStatement,
		std::shared_ptr<IStatement> negativeStatement
	);
	CIfStm();
	void Accept(IVisitor &visitor) override;

	std::shared_ptr<IExpression> conditionExpression;
	std::shared_ptr<IStatement> positiveStatement;
	std::shared_ptr<IStatement> negativeStatement;
};


//CWhileStm:
//-------------------------------------------------------------------------------------------------

class CWhileStm : public IStatement {
public:
	CWhileStm(
		std::shared_ptr<IExpression> conditionExpression,
		std::shared_ptr<IStatement> statement
	);
	CWhileStm();
	void Accept(IVisitor &visitor) override;

	std::shared_ptr<IExpression> conditionExpression;
	std::shared_ptr<IStatement> statement;
};
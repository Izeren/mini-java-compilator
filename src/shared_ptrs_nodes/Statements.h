#pragma once

#include "../INode.h"

class IStatement : public INode {};

class CAssignStm : public IStatement {
public:
	CAssignStm(std::shared_ptr<CIdExp> leftExpression, std::shared_ptr<IExpression> rightExpression);
	CAssignStm();
	void Accept(IVisitor &visitor) override;

	std::shared_ptr<CIdExp> leftExpression;
	std::shared_ptr<IExpression> rightExpression;
};

class CCompoundStm : public IStatement {
public:
	CCompoundStm();
	CCompoundStm(std::shared_ptr<IStatement> leftStatement, std::shared_ptr<IStatement> rightStatement);
	void Accept(IVisitor &visitor) override;

	std::shared_ptr<IStatement> leftStatement;
	std::shared_ptr<IStatement> rightStatement;
};

class CPrintStm : public IStatement {
public:
	CPrintStm();
	CPrintStm(std::shared_ptr<IStatement> expression);

	void Accept(IVisitor &visitor) override;

	std::shared<IExpression> expression;
};

class CSimpleStm : public IStatement {
public:
	CSimpleStm();
	CSimpleStm(std::shared_ptr<IStatement> statement);
	void Accept(IVisitor &visitor) override;

	std::shared_ptr<IStatement> statement;
};
#include "Statements.h"

//CAssignStm:
//-------------------------------------------------------------------------------------------------

CAssignStm::CAssignStm() : CAssignStm(NULL, NULL) {}

CAssignStm::CAssignStm(
	std::shared_ptr<CIdExp> leftExpression,
	std::shared_ptr<IExpression> rightExpression
) {
	this->leftExpression = leftExpression;
	this->rightExpression = rightExpression;
}


void CAssignStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CCompoundStm:
//-------------------------------------------------------------------------------------------------

CCompoundStm::CCompoundStm() : CCompoundStm(NULL, NULL) {}

CCompoundStm::CCompoundStm(
	std::shared_ptr<IStatement> leftStatement,
	std::shared_ptr<IStatement> rightStatement
) {
	this->leftStatement = leftStatement;
	this->rightStatement = rightStatement;
}

void CCompoundStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CPrintStm:
//-------------------------------------------------------------------------------------------------

CPrintStm::CPrintStm() : CPrintStm(NULL) {}

CPrintStm::CPrintStm(std::shared_ptr<IExpression> expression) {
	this->expression = expression;
}

void CPrintStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CSimpleStm:
//-------------------------------------------------------------------------------------------------

CSimpleStm::CSimpleStm() : CSimpleStm(NULL) {}

CSimpleStm::CSimpleStm(std::shared_ptr<IStatement> statement) {
	this->statement = statement;
}

void CSimpleStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CIfStm:
//-------------------------------------------------------------------------------------------------

CIfStm::CIfStm() : CIfStm(NULL, NULL, NULL) {}

CIfStm::CIfStm(
	std::shared_ptr<IExpression> conditionExpression,
	std::shared_ptr<IStatement> positiveStatement,
	std::shared_ptr<IStatement> negativeStatement
) {
	this->conditionExpression = conditionExpression;
	this->positiveStatement = positiveStatement;
	this->negativeStatement = negativeStatement;
}


void CIfStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CWhileStm:
//-------------------------------------------------------------------------------------------------

CWhileStm::CWhileStm() : CWhileStm(NULL, NULL) {}

CWhileStm::CWhileStm(
	std::shared_ptr<IExpression> conditionExpression,
	std::shared_ptr<IStatement> statement
) {
	this->conditionExpression = conditionExpression;
	this->statement = statement;
}


void CWhileStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}
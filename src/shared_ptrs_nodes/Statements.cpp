#include "Statements.h"

//CAssignStm:
//-------------------------------------------------------------------------------------------------

CAssignStm::CAssignStm() {
	this->CAssignStm(NULL, NULL);
}

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

CCompoundStm::CCompoundStm() {
	this->CCompoundStm(NULL, NULL);
}

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

CPrintStm::CPrintStm() {
	this->CPrintStm(NULL);
}

CPrintStm::CPrintStm(std::shared_ptr<IExpression> expression) {
	this->expression = expression;
}

void CPrintStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

//CSimpleStm:
//-------------------------------------------------------------------------------------------------

CSimpleStm() {
	this->CSimpleStm(NULL);
}

CSimpleStm::CSimpleStm(std::shared_ptr<IStatement> statement) {
	this->statement = statement;
}

void CSimpleStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}
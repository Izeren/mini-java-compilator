#include "Statements.h"

#include <iostream>

//CAssignStm:
//-------------------------------------------------------------------------------------------------

CAssignStm::CAssignStm() : CAssignStm(NULL, NULL) {}

CAssignStm::CAssignStm(
	CIdExp* leftExpression,
	IExpression* rightExpression
) {
	this->position = leftExpression->position + rightExpression->position;
	this->leftExpression = std::unique_ptr<CIdExp>(leftExpression);
	this->rightExpression = std::unique_ptr<IExpression>(rightExpression);
}


void CAssignStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CAssignSubscriptStm:
//-------------------------------------------------------------------------------------------------

CAssignSubscriptStm::CAssignSubscriptStm() :CAssignSubscriptStm(NULL, NULL, NULL) {}

CAssignSubscriptStm::CAssignSubscriptStm(
	CIdExp* idExpression,
	IExpression* offset,
	IExpression* valueExpression
) {
	this->position = idExpression->position + valueExpression->position;
	this->idExpression = std::unique_ptr<CIdExp>(idExpression);
	this->indexExpression = std::unique_ptr<IExpression>(offset);
	this->valueExpression = std::unique_ptr<IExpression>(valueExpression);
}

void CAssignSubscriptStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CCompoundStm:
//-------------------------------------------------------------------------------------------------

CCompoundStm::CCompoundStm() : CCompoundStm(NULL, NULL) {}

CCompoundStm::CCompoundStm(
	IStatement* leftStatement,
	IStatement* rightStatement
) {
	this->leftStatement = std::unique_ptr<IStatement>(leftStatement);
	this->rightStatement = std::unique_ptr<IStatement>(rightStatement);
}

void CCompoundStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CPrintStm:
//-------------------------------------------------------------------------------------------------

CPrintStm::CPrintStm() : CPrintStm(NULL) {}

CPrintStm::CPrintStm(IExpression* expression) {
	this->expression = std::unique_ptr<IExpression>(expression);
    position = expression->position;
}

void CPrintStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CIfStm:
//-------------------------------------------------------------------------------------------------

CIfStm::CIfStm() : CIfStm(NULL, NULL, NULL) {}

CIfStm::CIfStm(
	IExpression* conditionExpression,
	IStatement* positiveStatement,
	IStatement* negativeStatement
) {
    this->position = conditionExpression->position + negativeStatement->position;
	this->conditionExpression = std::unique_ptr<IExpression>(conditionExpression);
	this->positiveStatement = std::unique_ptr<IStatement>(positiveStatement);
	this->negativeStatement = std::unique_ptr<IStatement>(negativeStatement);
}


void CIfStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CWhileStm:
//-------------------------------------------------------------------------------------------------

CWhileStm::CWhileStm() : CWhileStm(NULL, NULL) {}

CWhileStm::CWhileStm(
	IExpression* conditionExpression,
	IStatement* statement
) {
	this->position = conditionExpression->position;
	this->conditionExpression = std::unique_ptr<IExpression>(conditionExpression);
	this->statement = std::unique_ptr<IStatement>(statement);
}


void CWhileStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}
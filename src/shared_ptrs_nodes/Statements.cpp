#include "Statements.h"

#include <iostream>

//CAssignStm:
//-------------------------------------------------------------------------------------------------

CAssignStm::CAssignStm() : CAssignStm(NULL, NULL) {}

CAssignStm::CAssignStm(
	CIdExp* leftExpression,
	IExpression* rightExpression
) {
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
	CNumExp* offset,
	IExpression* valueExpression
) {
	this->idExpression = std::unique_ptr<CIdExp>(idExpression);
	this->offset = std::unique_ptr<CNumExp>(offset);
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
    std::cout << "PRINTLN POSITION" << position.GetStringPosition() << "\n";
}

void CPrintStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CSimpleStm:
//-------------------------------------------------------------------------------------------------

CSimpleStm::CSimpleStm() : CSimpleStm(NULL) {}

CSimpleStm::CSimpleStm(IStatement* statement) {
	this->statement = std::unique_ptr<IStatement>(statement);
}

void CSimpleStm::Accept(IVisitor &visitor) {
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
	this->conditionExpression = std::unique_ptr<IExpression>(conditionExpression);
	this->statement = std::unique_ptr<IStatement>(statement);
}


void CWhileStm::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}
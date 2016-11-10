#include "Expressions.h"
#include "Classes.h"
#include <cstring>
#include <iostream>

//CIdExp:
//-------------------------------------------------------------------------------------------------

CIdExp::CIdExp(char *name, int *address) {
	this->name = std::string(name);
	this->address = address;
}

void CIdExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

//CIdPtrExp:
//-------------------------------------------------------------------------------------------------

CIdPtrExp::CIdPtrExp(const std::string &name, int *address) {
	this->name = name;
	this->address = address;
}

CIdPtrExp::CIdPtrExp() : CIdPtrExp(BAD_ID) {}

void CIdPtrExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}



//CNumExp:
//-------------------------------------------------------------------------------------------------

CNumExp::CNumExp(const char* number) {
	std::cout << "test->" << number << "<-test\n";
	this->number = atoi(number);
}

void CNumExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//COpExp:
//-------------------------------------------------------------------------------------------------

std::map<enums::TOperation, std::string> COpExp::stringOperations = {
	{ enums::TOperation::PLUS, "+" },
	{ enums::TOperation::MINUS, "-" },
	{ enums::TOperation::MULTIPLY, "*" },
	{ enums::TOperation::MOD, "%" }
};

void COpExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

COpExp::COpExp(
	IExpression* leftOperand,
	IExpression* rightOperand,
	enums::TOperation operation
) {
	this->leftOperand = std::unique_ptr<IExpression>(leftOperand);
	this->rightOperand = std::unique_ptr<IExpression>(rightOperand);
	this->operation = operation;
}

COpExp::COpExp() : COpExp(NULL, NULL) {}


//CLogExp:
//-------------------------------------------------------------------------------------------------
CLogExp::CLogExp(bool variable) {
	this->variable = variable;
}

void CLogExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//CLogOExp:
//-------------------------------------------------------------------------------------------------

std::map<enums::TLogicalOperation, std::string> CLogOpExp::stringOperations = {
	{ enums::TLogicalOperation::AND, "&&" },
	{ enums::TLogicalOperation::OR, "||" }
};

void CLogOpExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

CLogOpExp::CLogOpExp(
	IExpression* leftOperand,
	IExpression* rightOperand,
	enums::TLogicalOperation operation
) {
	this->leftOperand = std::unique_ptr<IExpression>(leftOperand);
	this->rightOperand = std::unique_ptr<IExpression>(rightOperand);
	this->operation = operation;
}


//CCompExp:
//-------------------------------------------------------------------------------------------------

std::map<enums::TCompareOperation, std::string> CCompExp::stringOperations = {
	{ enums::TCompareOperation::GREATER, ">" },
	{ enums::TCompareOperation::GREATER_OR_EQUAL, ">=" },
	{ enums::TCompareOperation::LESS, "<" },
	{ enums::TCompareOperation::LESS_OR_EQUAL, "<=" }
};

void CCompExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

CCompExp::CCompExp(
	IExpression* leftOperand,
	IExpression* rightOperand,
	enums::TCompareOperation operation
) {
	this->leftOperand = std::unique_ptr<IExpression>(leftOperand);
	this->rightOperand = std::unique_ptr<IExpression>(rightOperand);
	this->operation = operation;
}


//CUnarMinusExp:
//-------------------------------------------------------------------------------------------------
CUnarMinusExp::CUnarMinusExp(IExpression* rightOperand) {
	this->rightOperand = std::unique_ptr<IExpression>(rightOperand);
}

void CUnarMinusExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

//CGetLengthExp:
//-------------------------------------------------------------------------------------------------

CGetLengthExp::CGetLengthExp(CArrayExpression* _array)
{
	array = std::unique_ptr<CArrayExpression>(_array);
}

void CGetLengthExp::Accept (IVisitor& visitor)
{
	visitor.Visit(*this);
}

//CGetFieldExp:
//-------------------------------------------------------------------------------------------------

CGetFieldExp::CGetFieldExp(CClass* _classOwner, CField* _field)
{
	classOwner = std::unique_ptr<CClass>(_classOwner);
	field = std::unique_ptr<CField>(_field);
}

void CGetFieldExp::Accept (IVisitor& visitor)
{
	visitor.Visit(*this);
}

//CCallMethodExp:
//-------------------------------------------------------------------------------------------------

CCallMethodExp::CCallMethodExp(CClass* _classOwner, CIdExp* _methodName, CExpList* _args)
{
	classOwner = std::unique_ptr<CClass>(_classOwner);
	methodName = std::unique_ptr<CIdExp>(_methodName);
	args = std::unique_ptr<CExpList>(_args);
}

void CCallMethodExp::Accept(IVisitor& visitor)
{
	visitor.Visit(*this);
}

//CExpList:
//-------------------------------------------------------------------------------------------------

CExpList::CExpList() {
	exps = std::vector<std::unique_ptr<IExpression> >();
}

void CExpList::Add(IExpression* _exp) {
	exps.push_back(std::unique_ptr<IExpression>(_exp));
}

void CExpList::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

//CThisExpression:
//-------------------------------------------------------------------------------------------------
CThisExpression::CThisExpression() {
}

void CThisExpression::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

//CNegativeExpression:
//-------------------------------------------------------------------------------------------------

CNegativeExpression::CNegativeExpression(IExpression* expression) {
	this->expression = std::unique_ptr<IExpression>(expression);
}

void CNegativeExpression::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

//CArrayExpression:
//-------------------------------------------------------------------------------------------------

CArrayExpression::CArrayExpression(IExpression* lengthExpression) {
	this->lengthExpression = std::unique_ptr<IExpression>(lengthExpression);
}

void CArrayExpression::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

//CByIndexExpression:
//-------------------------------------------------------------------------------------------------

CByIndexExpression::CByIndexExpression(CArrayExpression* arrayExpression, IExpression* indexExpression) {
	this->arrayExpression = std::unique_ptr<CArrayExpression>(arrayExpression);
	this->indexExpression = std::unique_ptr<IExpression>(indexExpression);
}

void CByIndexExpression::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}
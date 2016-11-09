#include "Expressions.h"
#include "Classes.h"
#include <unordered_map>

//CIdExp:
//-------------------------------------------------------------------------------------------------

CIdExp::CIdExp(const std::string &name, int *address) {
	this->name = name;
	this->address = address;
}

CIdExp::CIdExp() : CIdExp(BAD_ID) {}

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

CNumExp::CNumExp(int number) {
	this->number = number;
}

void CNumExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}


//COpExp:
//-------------------------------------------------------------------------------------------------

std::map<TOperation, std::string> COpExp::stringOperations = {
	{ TOperation::PLUS, "+" },
	{ TOperation::MINUS, "-" },
	{ TOperation::MULTIPLY, "*" },
	{ TOperation::MOD, "%" }
};

void COpExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

COpExp::COpExp(
	IExpression* leftOperand,
	IExpression* rightOperand,
	TOperation operation
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

std::map<TLogicalOperation, std::string> CLogOpExp::stringOperations = {
	{ TLogicalOperation::AND, "&&" },
	{ TLogicalOperation::OR, "||" }
};

void CLogOpExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

CLogOpExp::CLogOpExp(
	IExpression* leftOperand,
	IExpression* rightOperand,
	TLogicalOperation operation
) {
	this->leftOperand = std::unique_ptr<IExpression>(leftOperand);
	this->rightOperand = std::unique_ptr<IExpression>(rightOperand);
	this->operation = operation;
}


//CCompExp:
//-------------------------------------------------------------------------------------------------

std::map<TCompareOperation, std::string> CCompExp::stringOperations = {
	{ TCompareOperation::GREATER, ">" },
	{ TCompareOperation::GREATER_OR_EQUAL, ">=" },
	{ TCompareOperation::LESS, "<" },
	{ TCompareOperation::LESS_OR_EQUAL, "<=" }
};

void CCompExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

CCompExp::CCompExp(
	IExpression* leftOperand,
	IExpression* rightOperand,
	TCompareOperation operation
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
	array = _array;
}

void CGetLengthExp::Accept (IVisitor& visitor) override
{
	visitor.Visit(*this);
}

//CGetFieldExp:
//-------------------------------------------------------------------------------------------------

CGetFieldExp::CGetFieldExp(CClass* _classOwner, CField* _field)
{
	classOwner = _classOwner;
	field = _field;
}

void CGetFieldExp::Accept (IVisitor& visitor) override
{
	visitor.Visit(*this);
}

//CCallMethodExp:
//-------------------------------------------------------------------------------------------------

CCallMethodExp::CCallMethodExp(CClass* _classOwner, CIdExp* _methodName, CExpList* _args)
{
	classOwner = _classOwner;
	methodName = _methodName;
	args = _args;
}

void CCallMethodExp::Accept(IVisitor& visitor) override
{
	visitor.Visit(*this);
}


//CExpList:
//-------------------------------------------------------------------------------------------------

CExpList::CExpList(IExpression* _exp, CExpList* _expList)
{
	exp = _exp;
	expList = _expList;
}

void CExpList::Accept(IVisitor& visitor) override
{
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
#include "Expressions.h"
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
	{ TOperation::MULTIPLY, "*" }
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
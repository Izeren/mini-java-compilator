#include "Expressions.h"

//CIdExp:
//-------------------------------------------------------------------------------------------------
CIdExp::CIdExp(const std::string &name, int *address) {
	this->name = name;
	this->address = address;
}

CIdExp::CIdExp() {
	this->CIdExp(BAD_ID);
}

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

void COpExp::Accept(IVisitor &visitor) {
	visitor.Visit(*this);
}

COpExp::COpExp(
	std::shared_ptr<IExpression> leftOperand, 
	std::shared_ptr<IExpression> rightOperand, 
	TOperation operation
) {

	this->leftOperand = leftOperand;
	this->rightOperand = rightOperand;
	this->operation = operation;

}

COpExp::COpExp() {
	this->COpExp(NULL, NULL);
}
#include "Expressions.h"
#include "Classes.h"
#include <cstring>
#include <iostream>
//#include "../symbol_table/SymbolInfo.h"
//CIdExp:
//-------------------------------------------------------------------------------------------------

CIdExp::CIdExp( char *name) {
    this->name = std::string( name );
}

void CIdExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

//CIdPtrExp:
//-------------------------------------------------------------------------------------------------

CIdPtrExp::CIdPtrExp( const std::string &name, int *address ) {
    this->name = name;
    this->address = address;
}

CIdPtrExp::CIdPtrExp() : CIdPtrExp( BAD_ID ) {}

void CIdPtrExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}



//CNumExp:
//-------------------------------------------------------------------------------------------------

CNumExp::CNumExp( const char *number ) {
    this->number = atoi( number );
}

void CNumExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}


//COpExp:
//-------------------------------------------------------------------------------------------------

std::map<enums::TOperation, std::string> COpExp::stringOperations = {
        {enums::TOperation::PLUS,     "+"},
        {enums::TOperation::MINUS,    "-"},
        {enums::TOperation::MULTIPLY, "*"},
        {enums::TOperation::MOD,      "%"}
};

void COpExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

COpExp::COpExp(
        IExpression *leftOperand,
        IExpression *rightOperand,
        enums::TOperation operation
) {
    this->position = leftOperand->position + rightOperand->position;
    this->leftOperand = std::unique_ptr<IExpression>( leftOperand );
    this->rightOperand = std::unique_ptr<IExpression>( rightOperand );
    this->operation = operation;
}

COpExp::COpExp() : COpExp( NULL, NULL ) {}


//CLogExp:
//-------------------------------------------------------------------------------------------------
CLogExp::CLogExp( bool variable ) {
    this->variable = variable;
}

void CLogExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}


//CLogOExp:
//-------------------------------------------------------------------------------------------------

std::map<enums::TLogicalOperation, std::string> CLogOpExp::stringOperations = {
        {enums::TLogicalOperation::AND, "&&"},
        {enums::TLogicalOperation::OR,  "||"}
};

void CLogOpExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

CLogOpExp::CLogOpExp(
        IExpression *leftOperand,
        IExpression *rightOperand,
        enums::TLogicalOperation operation
) {
    this->position = leftOperand->position + rightOperand->position;
    this->leftOperand = std::unique_ptr<IExpression>( leftOperand );
    this->rightOperand = std::unique_ptr<IExpression>( rightOperand );
    this->operation = operation;
}


//CCompExp:
//-------------------------------------------------------------------------------------------------

std::map<enums::TCompareOperation, std::string> CCompExp::stringOperations = {
        {enums::TCompareOperation::GREATER,          ">"},
        {enums::TCompareOperation::GREATER_OR_EQUAL, ">="},
        {enums::TCompareOperation::LESS,             "<"},
        {enums::TCompareOperation::LESS_OR_EQUAL,    "<="}
};

void CCompExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

CCompExp::CCompExp(
        IExpression *leftOperand,
        IExpression *rightOperand,
        enums::TCompareOperation operation
) {
    this->position = leftOperand->position + rightOperand->position;
    this->leftOperand = std::unique_ptr<IExpression>( leftOperand );
    this->rightOperand = std::unique_ptr<IExpression>( rightOperand );
    this->operation = operation;
}


//CUnarMinusExp:
//-------------------------------------------------------------------------------------------------
CUnarMinusExp::CUnarMinusExp( IExpression *rightOperand ) {
    this->position = rightOperand->position;
    this->rightOperand = std::unique_ptr<IExpression>( rightOperand );
}

void CUnarMinusExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

//CGetLengthExp:
//-------------------------------------------------------------------------------------------------

CGetLengthExp::CGetLengthExp( IExpression *_array ) {
    position = _array->position;
    arrayIdentifier = std::unique_ptr<IExpression>( _array );
}

void CGetLengthExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

//CCallMethodExp:
//-------------------------------------------------------------------------------------------------

CCallMethodExp::CCallMethodExp( IExpression* _objectExpression, CIdExp *_methodName, CExpList *_args ) {
    this->position = _methodName->position;
    objectExpression = std::unique_ptr<IExpression>(_objectExpression);
    methodName = std::unique_ptr<CIdExp>( _methodName );
    args = std::unique_ptr<CExpList>( _args );
}

void CCallMethodExp::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

//CExpList:
//-------------------------------------------------------------------------------------------------

CExpList::CExpList() {
    exps = std::vector<std::unique_ptr<IExpression> >();
}

CExpList::CExpList( IExpression *_exp ) {
    this->exps = std::vector<std::unique_ptr<IExpression> >();
    this->exps.push_back( std::unique_ptr<IExpression>( _exp ));
    this->position = _exp->position;
}

void CExpList::Add( IExpression *_exp ) {
    exps.push_back( std::unique_ptr<IExpression>( _exp ));
    this->position = this->position + _exp->position;
}

void CExpList::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

//CNegativeExpression:
//-------------------------------------------------------------------------------------------------

CNegativeExpression::CNegativeExpression( IExpression *expression ) {
    this->position = expression->position;
    this->expression = std::unique_ptr<IExpression>( expression );
}

void CNegativeExpression::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

//CNewArrayExpression:
//-------------------------------------------------------------------------------------------------

CNewArrayExpression::CNewArrayExpression( IExpression *lengthExpression ) {
    this->position = lengthExpression->position;
    this->lengthExpression = std::unique_ptr<IExpression>( lengthExpression );
}

void CNewArrayExpression::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

//CNewIdentifier:
//-------------------------------------------------------------------------------------------------

CNewIdentifier::CNewIdentifier( CIdExp *identifier ) {
    this->identifier = std::unique_ptr<CIdExp>( identifier );
    this->position = identifier->position;
}

void CNewIdentifier::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}


//CByIndexExpression:
//-------------------------------------------------------------------------------------------------

CByIndexExpression::CByIndexExpression( IExpression *arrayExpression, IExpression *indexExpression ) {
    this->position = arrayExpression->position;
    this->identifier = std::unique_ptr<IExpression>( arrayExpression );
    this->indexExpression = std::unique_ptr<IExpression>( indexExpression );
}

void CByIndexExpression::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

//CThisExpression
//-------------------------------------------------------------------------------------------------

CThisExpression::CThisExpression() {

}

void CThisExpression::Accept(IVisitor &visitor) {
    visitor.Visit( *this );
}

CGetFieldByThisExpression::CGetFieldByThisExpression(CIdExp *_identifier) {
    fieldIdentifier = std::unique_ptr<CIdExp>(_identifier);
}

void CGetFieldByThisExpression::Accept(IVisitor &visitor) {
    visitor.Visit( *this );
}

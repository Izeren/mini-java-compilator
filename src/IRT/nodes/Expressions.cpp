//
// Created by izeren on 2/19/17.
//
#include "Expressions.h"

void IRT::CEseqExpression::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CEseqExpression::~CEseqExpression() {

}

const IRT::CStatement *IRT::CEseqExpression::getStatement() const {
    return statement.get();
}

const IRT::CExpression *IRT::CEseqExpression::getExpression() const {
    return expression.get();
}

IRT::CEseqExpression::CEseqExpression( std::unique_ptr<const IRT::CStatement> _statement,
                                       std::unique_ptr<const IRT::CExpression> _expression ) : statement(
        std::move( _statement )), expression( std::move( _expression )) {}

void IRT::CBinopExpression::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CBinopExpression::~CBinopExpression() {

}

IRT::CBinopExpression::CBinopExpression( std::unique_ptr<const IRT::CExpression> _leftOperand,
                                         std::unique_ptr<const IRT::CExpression> _rightOperand,
                                         IRT::enums::TOperationType _operation ) : leftOperand( std::move( _leftOperand )),
                                                                                 rightOperand(
                                                                                         std::move( _rightOperand )),
                                                                                 operation( _operation ) {}

const IRT::CExpression *IRT::CBinopExpression::getLeftOperand() const {
    return leftOperand.get();
}

const IRT::CExpression *IRT::CBinopExpression::getRightOperand() const {
    return rightOperand.get();
}

IRT::enums::TOperationType IRT::CBinopExpression::getOperation() const {
    return operation;
}

void IRT::CConstExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CConstExpression::~CConstExpression() {

}

IRT::CConstExpression::CConstExpression( int _value ) : value( _value ) {}

int IRT::CConstExpression::getValue() const {
    return value;
}

void IRT::CTempExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CTempExpression::~CTempExpression() {

}

IRT::CTempExpression::CTempExpression( const IRT::CTemp &_temprorary ) : temprorary( _temprorary ) {}

const IRT::CTemp &IRT::CTempExpression::getTemprorary() const {
    return temprorary;
}

void IRT::CNameExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CNameExpression::~CNameExpression() {

}

IRT::CNameExpression::CNameExpression( const IRT::CLabel &_label ) : label( _label ) {}

const IRT::CLabel &IRT::CNameExpression::getLabel() const {
    return label;
}

void IRT::CCallExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CCallExpression::~CCallExpression() {

}

const IRT::CExpression *IRT::CCallExpression::getFunction() const {
    return function.get();
}

const IRT::CExpressionList *IRT::CCallExpression::getArgumetns() const {
    return argumetns.get();
}

IRT::CCallExpression::CCallExpression(  std::unique_ptr<const IRT::CExpression> _function,
                                        std::unique_ptr<const IRT::CExpressionList> _argumetns ) : function(
        std::move(_function )), argumetns( std::move(_argumetns )) {}

void IRT::CMemExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CMemExpression::~CMemExpression() {

}

IRT::CMemExpression::CMemExpression(  std::unique_ptr<const IRT::CExpression> _address ) : address( std::move(_address )) {}

const IRT::CExpression *IRT::CMemExpression::getAddress() const {
    return address.get();
}

void IRT::CExpressionList::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CExpressionList::~CExpressionList() {

}

const std::vector<std::unique_ptr<const IRT::CExpression>> &IRT::CExpressionList::getExpressions() const {
    return expressions;
}

IRT::CExpressionList::CExpressionList( const IRT::CExpression *_expression ) {
    Add( _expression );
}

IRT::CExpressionList::CExpressionList( std::unique_ptr<const IRT::CExpression> _expression ) {
    Add( std::move( _expression ));
}

void IRT::CExpressionList::Add( const IRT::CExpression *_expression ) {
    expressions.emplace_back( _expression );
}

void IRT::CExpressionList::Add( std::unique_ptr<const IRT::CExpression> _expression ) {
    expressions.push_back( std::move( _expression ));
}

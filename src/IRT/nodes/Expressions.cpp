//
// Created by izeren on 2/19/17.
//
#include "Expressions.h"
#include "Statements.h"

void IRT::CEseqExpression::Accept( IVisitor &visitor ) const {
    visitor.Visit( *this );
}

IRT::CEseqExpression::~CEseqExpression( ) {

}

const IRT::CStatement *IRT::CEseqExpression::getStatement( ) const {
    return statement.get( );
}

const IRT::CExpression *IRT::CEseqExpression::getExpression( ) const {
    return expression.get( );
}

IRT::CEseqExpression::CEseqExpression( std::unique_ptr<const IRT::CStatement> _statement,
                                       std::unique_ptr<const IRT::CExpression> _expression ) : statement(
        std::move( _statement )), expression( std::move( _expression )) { }

std::unique_ptr<const IRT::CExpression> IRT::CEseqExpression::Copy( ) const {
    return std::move(
            std::unique_ptr<const IRT::CExpression>( new CEseqExpression( statement->Copy( ), expression->Copy( ))));
}

void IRT::CBinopExpression::Accept( IVisitor &visitor ) const{
    visitor.Visit( *this );
}

IRT::CBinopExpression::~CBinopExpression( ) {

}

IRT::CBinopExpression::CBinopExpression( std::unique_ptr<const IRT::CExpression> _leftOperand,
                                         std::unique_ptr<const IRT::CExpression> _rightOperand,
                                         IRT::enums::TOperationType _operation ) :
        leftOperand( std::move( _leftOperand )),
        rightOperand( std::move( _rightOperand )),
        operation( _operation ) { }

const IRT::CExpression *IRT::CBinopExpression::getLeftOperand( ) const {
    return leftOperand.get( );
}

const IRT::CExpression *IRT::CBinopExpression::getRightOperand( ) const {
    return rightOperand.get( );
}

IRT::enums::TOperationType IRT::CBinopExpression::getOperation( ) const {
    return operation;
}

std::unique_ptr<const IRT::CExpression> IRT::CBinopExpression::Copy( ) const {
    return std::move( std::unique_ptr<const IRT::CExpression>(
            new CBinopExpression( leftOperand->Copy( ), rightOperand->Copy( ), operation )));
}

void IRT::CConstExpression::Accept( IRT::IVisitor &visitor ) const {
    visitor.Visit( *this );
}

IRT::CConstExpression::~CConstExpression( ) {

}

IRT::CConstExpression::CConstExpression( int _value ) : value( _value ) { }

int IRT::CConstExpression::getValue( ) const {
    return value;
}

std::unique_ptr<const IRT::CExpression> IRT::CConstExpression::Copy( ) const {
    return std::move( std::unique_ptr<const IRT::CExpression>( new CConstExpression( value )));
}

void IRT::CTempExpression::Accept( IRT::IVisitor &visitor ) const{
    visitor.Visit( *this );
}

IRT::CTempExpression::~CTempExpression( ) {

}

IRT::CTempExpression::CTempExpression( const IRT::CTemp &_temprorary ) : temprorary( _temprorary ) { }

const IRT::CTemp &IRT::CTempExpression::getTemprorary( ) const {
    return temprorary;
}

std::unique_ptr<const IRT::CExpression> IRT::CTempExpression::Copy( ) const {
    return std::move( std::unique_ptr<const IRT::CExpression>( new CTempExpression( temprorary )));
}

void IRT::CNameExpression::Accept( IRT::IVisitor &visitor ) const {
    visitor.Visit( *this );
}

IRT::CNameExpression::~CNameExpression( ) {

}

IRT::CNameExpression::CNameExpression( const IRT::CLabel &_label ) : label( _label ) { }

const IRT::CLabel &IRT::CNameExpression::getLabel( ) const {
    return label;
}

std::unique_ptr<const IRT::CExpression> IRT::CNameExpression::Copy( ) const {
    return std::move( std::unique_ptr<const IRT::CExpression>( new CNameExpression( label )));
}

void IRT::CCallExpression::Accept( IRT::IVisitor &visitor ) const {
    visitor.Visit( *this );
}

IRT::CCallExpression::~CCallExpression( ) {

}

const IRT::CExpression *IRT::CCallExpression::getFunction( ) const {
    return function.get( );
}

const IRT::CExpressionList *IRT::CCallExpression::getArgumetns( ) const {
    return arguments.get( );
}

IRT::CCallExpression::CCallExpression( std::unique_ptr<const IRT::CExpression> _function,
                                       std::unique_ptr<const IRT::CExpressionList> _argumetns ) : function(
        std::move( _function )), arguments( std::move( _argumetns )) { }

std::unique_ptr<const IRT::CExpression> IRT::CCallExpression::Copy( ) const {
    return std::move(
            std::unique_ptr<const IRT::CExpression>( new CCallExpression( function->Copy( ), arguments->Copy( ))));
}

void IRT::CMemExpression::Accept( IRT::IVisitor &visitor ) const {
    visitor.Visit( *this );
}

IRT::CMemExpression::~CMemExpression( ) {

}

IRT::CMemExpression::CMemExpression( std::unique_ptr<const IRT::CExpression> _address ) : address(
        std::move( _address )) { }

const IRT::CExpression *IRT::CMemExpression::getAddress( ) const {
    return address.get( );
}

std::unique_ptr<const IRT::CExpression> IRT::CMemExpression::Copy( ) const {
    return std::move( std::unique_ptr<const IRT::CExpression>( new CMemExpression( address->Copy( ))));
}

void IRT::CExpressionList::Accept( IRT::IVisitor &visitor ) const {
    visitor.Visit( *this );
}

IRT::CExpressionList::~CExpressionList( ) {

}

const std::vector<std::unique_ptr<const IRT::CExpression>> &IRT::CExpressionList::getExpressions( ) const {
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

std::unique_ptr<const IRT::CExpression> IRT::CExpressionList::Copy( ) const {
    CExpressionList *newList = new CExpressionList( );
    for ( auto it : expressions ) {
        newList->Add( std::move( it->Copy( )));
    }
    return std::move( std::unique_ptr<const CExpression>( newList ));
}

//
// Created by izeren on 4/24/17.
//
#include "CLinearizeVisitor.h"

IRT::CLinearizeVisitor::CLinearizeVisitor( ) {
    statementList = std::unique_ptr<CStatementList>(new CStatementList());
}

IRT::CLinearizeVisitor::~CLinearizeVisitor( ) {

}

std::unique_ptr<const IRT::CStatementList> IRT::CLinearizeVisitor::ResultTree( ) {
    return std::move( statementList );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CEseqExpression &expression ) {
    assert( false );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CBinopExpression &expression ) {
    assert( false );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CConstExpression &expression ) {
    assert( false );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CTempExpression &expression ) {
    assert( false );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CNameExpression &expression ) {
    assert( false );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CCallExpression &expression ) {
    assert( false );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CMemExpression &expression ) {
    assert( false );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CExpressionList &expression ) {
    assert( false );
}

void IRT::CLinearizeVisitor::Visit( const IRT::CMoveStatement &statement ) {
    statementList->Add( std::move( statement.Copy( )));
}

void IRT::CLinearizeVisitor::Visit( const IRT::CExpStatement &statement ) {
    statementList->Add( std::move( statement.Copy( )));
}

void IRT::CLinearizeVisitor::Visit( const IRT::CLabelStatement &statement ) {
    statementList->Add( std::move( statement.Copy( )));
}

void IRT::CLinearizeVisitor::Visit( const IRT::CJumpStatement &statement ) {
    statementList->Add( std::move( statement.Copy( )));
}

void IRT::CLinearizeVisitor::Visit( const IRT::CJumpConditionalStatement &statement ) {
    statementList->Add( std::move( statement.Copy( )));
}

void IRT::CLinearizeVisitor::Visit( const IRT::CSeqStatement &statement ) {
    if ( statement.LeftStatement( )) {
        statement.LeftStatement( )->Accept( *this );
    }
    if ( statement.RightStatement( )) {
        statement.RightStatement( )->Accept( *this );
    }
}

void IRT::CLinearizeVisitor::Visit( const IRT::CStatementList &statement ) {
    assert( false );
}

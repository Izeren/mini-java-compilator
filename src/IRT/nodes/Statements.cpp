#include <vector>
#include "Statements.h"
#include "Expressions.h"

using namespace IRT;


CMoveStatement::CMoveStatement( std::unique_ptr<const CExpression> _target,
                                std::unique_ptr<const CExpression> _source )
        : target( std::move( _target )),
          source( std::move( _source )) { }

const CExpression *CMoveStatement::Target( ) const {
    return target.get( );
}

const CExpression *CMoveStatement::Source( ) const {
    return source.get( );
}

void CMoveStatement::Accept( IVisitor &visitor ) const {
    visitor.Visit( *this );
}

std::unique_ptr<const CStatement> CMoveStatement::Copy( ) const {
    return std::move( std::unique_ptr<const CStatement>( new CMoveStatement( target->Copy( ), source->Copy( ))));
}

// ********************************************************************************

CExpStatement::CExpStatement( std::unique_ptr<const CExpression> _expression ) : expression(
        std::move( _expression )) { }

const CExpression *CExpStatement::Expression( ) const {
    return expression.get( );
}

void CExpStatement::Accept( IVisitor &visitor ) const {
    visitor.Visit( *this );
}

std::unique_ptr<const CStatement> CExpStatement::Copy( ) const {
    return std::move( std::unique_ptr<const CStatement>( new CExpStatement( expression->Copy( ))));
}

// ********************************************************************************

CJumpStatement::CJumpStatement( std::unique_ptr<const CLabelStatement> _label ) : label( std::move(_label) ) { }

const CLabelStatement* CJumpStatement::getLabel( ) const {
    return label.get();
}

void CJumpStatement::Accept( IVisitor &visitor ) const {
    visitor.Visit( *this );
}

std::unique_ptr<const CStatement> CJumpStatement::Copy( ) const {
    return std::move( std::unique_ptr<const CStatement>( new CJumpStatement( std::move(label->CastCopy()) )));
}

// ********************************************************************************

CJumpConditionalStatement::CJumpConditionalStatement( TLogicOperator _operation,
                                                      std::unique_ptr<const CExpression> left,
                                                      std::unique_ptr<const CExpression> right,
                                                      std::unique_ptr<const CLabelStatement> _labelTrue,
                                                      std::unique_ptr<const CLabelStatement> _labelFalse )
        : operation( _operation ),
          leftOperand( std::move( left )), rightOperand( std::move( right )),
          labelTrue( std::move( _labelTrue )), labelFalse( std::move( _labelFalse )) { }

const CExpression *CJumpConditionalStatement::LeftOperand( ) const {
    return leftOperand.get( );
}

const CExpression *CJumpConditionalStatement::RightOperand( ) const {
    return rightOperand.get( );
}

const CLabelStatement *CJumpConditionalStatement::TrueLabel( ) const {
    return labelTrue.get( );
}

const CLabelStatement *CJumpConditionalStatement::FalseLabel( ) const {
    return labelFalse.get( );
}

void CJumpConditionalStatement::Accept( IVisitor &visitor ) const {
    visitor.Visit( *this );
}

TLogicOperator CJumpConditionalStatement::Operation( ) const {
    return operation;
}

std::unique_ptr<const CStatement> CJumpConditionalStatement::Copy( ) const {
    return std::move( std::unique_ptr<const CStatement>(
            new CJumpConditionalStatement( operation,
                                           leftOperand->Copy( ),
                                           rightOperand->Copy( ),
                                           labelTrue->CastCopy( ),
                                           labelFalse->CastCopy( ))));
}

// ********************************************************************************

CSeqStatement::CSeqStatement( std::unique_ptr<const CStatement> _left, std::unique_ptr<const CStatement> _right )
        : leftStatement( std::move( _left )), rightStatement( std::move( _right )) { }

const CStatement *CSeqStatement::LeftStatement( ) const {
    return leftStatement.get( );
}

const CStatement *CSeqStatement::RightStatement( ) const {
    return rightStatement.get( );
}

void CSeqStatement::Accept( IVisitor &visitor ) const {
    visitor.Visit( *this );
}

std::unique_ptr<const CStatement> CSeqStatement::Copy( ) const {
    return std::move(
            std::unique_ptr<const CStatement>( new CSeqStatement( leftStatement->Copy( ), rightStatement->Copy( ))));
}

// ********************************************************************************

CLabelStatement::CLabelStatement( CLabel _label ) : label( _label ) { }

CLabel CLabelStatement::Label( ) const {
    return label;
}

void CLabelStatement::Accept( IVisitor &visitor ) const {
    visitor.Visit( *this );
}

std::unique_ptr<const CStatement> CLabelStatement::Copy( ) const {
    return std::move( std::unique_ptr<const CStatement>( new CLabelStatement( label )));
}

std::unique_ptr<const CLabelStatement> CLabelStatement::CastCopy( ) const {
    return std::move( std::unique_ptr<const CLabelStatement>( new CLabelStatement( label )));
}

// ********************************************************************************

CStatementList::CStatementList( ) { }

CStatementList::CStatementList( std::unique_ptr<const CStatement> &statement ) {
    Add( std::move(statement) );
}

void CStatementList::Add( std::unique_ptr<const CStatement> statement ) {
    statements.push_back( std::move( statement ));
}

const std::vector<std::unique_ptr<const CStatement>> &CStatementList::Statements( ) const {
    return statements;
}

std::vector<std::unique_ptr<const CStatement>> &CStatementList::StatementsNotConst( ) {
    return statements;
}

void CStatementList::Accept( IVisitor &visitor ) const {
    visitor.Visit( *this );
}

std::unique_ptr<const CStatement> CStatementList::Copy( ) const {
    return nullptr;
}

CStatementList *CStatementList::CopyNotConst() const {
    CStatementList* list = new CStatementList();
    for (int i = 0; i < statements.size(); ++i) {
        list->Add(std::move(statements[i]->Copy()));
    }

    return list;
}

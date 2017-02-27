#include <vector>
#include "Statements.h"
#include "../utils/Label.h"
#include "../utils/enums.h"

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

void CMoveStatement::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

// ********************************************************************************

CExpStatement::CExpStatement( std::unique_ptr<const CExpression> _expression ) : expression(
        std::move( _expression )) { }

const CExpression *CExpStatement::Expression( ) const {
    return expression.get( );
}

void CExpStatement::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

// ********************************************************************************

CJumpStatement::CJumpStatement( CLabel _target ) : target( _target ) { }

CLabel CJumpStatement::Target( ) const {
    return target;
}

void CJumpStatement::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

// ********************************************************************************

CJumpConditionalStatement::CJumpConditionalStatement( TLogicOperator _operation,
                                                      std::unique_ptr<const CExpression> left,
                                                      std::unique_ptr<const CExpression> right,
                                                      CLabel _labelTrue,
                                                      CLabel _labelFalse )
        : operation( _operation ),
          leftOperand( std::move( left )), rightOperand( std::move( right )),
          labelTrue( _labelTrue ), labelFalse( _labelFalse ) { }

const CExpression *CJumpConditionalStatement::LeftOperand( ) const {
    return leftOperand.get();
}

const CExpression *CJumpConditionalStatement::RightOperand( ) const {
    return rightOperand.get();
}

CLabel CJumpConditionalStatement::TrueLabel( ) const {
    return labelTrue;
}

CLabel CJumpConditionalStatement::FalseLabel( ) const {
    return labelFalse;
}

void CJumpConditionalStatement::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

// ********************************************************************************

CSeqStatement::CSeqStatement( std::unique_ptr<const CStatement> _left, std::unique_ptr<const CStatement> _right )
        : leftStatement( std::move( _left )), rightStatement( std::move( _right )) { }

const CStatement *CSeqStatement::LeftStatement( ) const {
    return leftStatement.get();
}

const CStatement *CSeqStatement::RightStatement( ) const {
    return rightStatement.get();
}

void CSeqStatement::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

// ********************************************************************************

CLabelStatement::CLabelStatement( CLabel _label ) : label( _label ) { }

CLabel CLabelStatement::Label( ) const {
    return label;
}

void CLabelStatement::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

// ********************************************************************************

CStatementList::CStatementList( ) { }

CStatementList::CStatementList( std::unique_ptr<const CStatement> statement ) {
    Add( std::move( statement ));
}

void CStatementList::Add( std::unique_ptr<const CStatement> &statement ) {
    statements.push_back( std::move( statement ));
}

const std::vector <std::unique_ptr<const CStatement>> &CStatementList::Statements( ) const {
    return statements;
}

void CStatementList::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

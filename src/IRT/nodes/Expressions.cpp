//
// Created by izeren on 2/19/17.
//
#include "Expressions.h"

void IRT::CEseqExpression::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CEseqExpression::~CEseqExpression() {

}

void IRT::CBinopExpression::Accept( IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CBinopExpression::~CBinopExpression() {

}

void IRT::CConstExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CConstExpression::~CConstExpression() {

}

void IRT::CTempExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CTempExpression::~CTempExpression() {

}

void IRT::CNameExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CNameExpression::~CNameExpression() {

}

void IRT::CCallExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CCallExpression::~CCallExpression() {

}

void IRT::CMemExpression::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CMemExpression::~CMemExpression() {

}

void IRT::CExpressionList::Accept( IRT::IVisitor &visitor ) {
    visitor.Visit( *this );
}

IRT::CExpressionList::~CExpressionList() {

}

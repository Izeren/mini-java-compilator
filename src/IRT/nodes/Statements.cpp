#include "Statements.h"

using namespace IRT;


CStatement::CStatement() {}

void CStatement::Accept( IVisitor *visitor ) const {

}


CMoveStatement::CMoveStatement( std::unique_ptr<const CExpression> _target,
                               std::unique_ptr<const CExpression> _source )
        : target( std::move(_target) ),
          source( std::move(_source) ) {}

const CExpression* CMoveStatement::Target() const {
    return target.get();
}

const CExpression* CMoveStatement::Source() const {
    return source.get();
}


#include "PrintVisitor.h"
#include "../utils/maps.h"

void IRT::PrintVisitor::Visit( const IRT::CEseqExpression &expression ) {
    std::vector<const IRT::INode *> children = { expression.getStatement( ), expression.getExpression( ) };
    ChildrenAnswers answers = VisitChildren( children );

    AddChildrenAnswers( answers );
    AddLabel( "Eseq" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CBinopExpression &expression ) {
    std::vector<const IRT::INode *> children = { expression.getLeftOperand( ), expression.getRightOperand( ) };
    ChildrenAnswers answers = VisitChildren( children );

    int operationId = ++lastVisited;
    std::string operationDescription = ConstructLabel( IRT::maps::operationTypeToString.at( expression.getOperation( )),
                                                       operationId );
    answers.PushBack( operationDescription, operationId );

    AddChildrenAnswers( answers );
    AddLabel( "BinopExp" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CConstExpression &expression ) {
    ++lastVisited;
    description = ConstructLabel( std::to_string( expression.getValue( )), lastVisited );
    AddArrow( lastVisited );
    AddLabel( "Const" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CTempExpression &expression ) {
    ++lastVisited;
    description = ConstructLabel( expression.getTemprorary( ).ToString( ), lastVisited );
    AddArrow( lastVisited );
    AddLabel( "Temp" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CNameExpression &expression ) {
    ++lastVisited;
    description = ConstructLabel( expression.getLabel( ).ToString( ), lastVisited );
    AddArrow( lastVisited );
    AddLabel( "Name" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CCallExpression &expression ) {
    std::vector<const IRT::INode *> children;
    children.push_back( expression.getFunction( ));
    for ( int i = 0; i < expression.getArguments( )->getExpressions( ).size( ); ++i ) {
        children.push_back( expression.getArguments( )->getExpressions( )[ i ].get( ));
    }
    ChildrenAnswers answers = VisitChildren( children );

    AddChildrenAnswers( answers );
    AddLabel( "Call" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CMemExpression &expression ) {
    std::vector<const IRT::INode *> children = { expression.getAddress( ) };
    ChildrenAnswers answers = VisitChildren( children );

    AddChildrenAnswers( answers );
    AddLabel( "Mem" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CExpressionList &expression ) {
    std::vector<const IRT::INode *> children;
    for ( int i = 0; i < expression.getExpressions( ).size( ); ++i ) {
        children.push_back( expression.getExpressions( )[ i ].get( ));
    }
    ChildrenAnswers answers = VisitChildren( children );

    AddChildrenAnswers( answers );
    AddLabel( "ExpressionList" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CMoveStatement &statement ) {
    std::vector<const IRT::INode *> children = { statement.Target( ), statement.Source( ) };
    ChildrenAnswers answers = VisitChildren( children );

    AddChildrenAnswers( answers );
    AddLabel( "Move" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CExpStatement &statement ) {
    std::vector<const IRT::INode *> children = { statement.Expression( ) };
    ChildrenAnswers answers = VisitChildren( children );

    AddChildrenAnswers( answers );
    AddLabel( "Exp" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CLabelStatement &statement ) {
    ++lastVisited;
    description = ConstructLabel( statement.Label( ).ToString( ), lastVisited );
    AddArrow( lastVisited );
    AddLabel( "Label" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CJumpStatement &statement ) {
    ++lastVisited;
    description = ConstructLabel( statement.Target( ).ToString( ), lastVisited );
    AddArrow( lastVisited );
    AddLabel( "Jump" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CJumpConditionalStatement &statement ) {
    std::vector<const IRT::INode *> children = { statement.LeftOperand( ), statement.RightOperand( ),
                                                 statement.TrueLabel( ), statement.FalseLabel( ) };
    ChildrenAnswers answers = VisitChildren( children );

    int operationId = ++lastVisited;
    std::string operationDescription = ConstructLabel( IRT::maps::logicOperationToString.at( statement.Operation( )),
                                                       operationId );
    answers.PushBack( operationDescription, operationId );

    AddChildrenAnswers( answers );
    AddLabel( "ConditionalJump" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CSeqStatement &statement ) {
    std::vector<const IRT::INode *> children = { statement.LeftStatement( ), statement.RightStatement( ) };
    ChildrenAnswers answers = VisitChildren( children );

    AddChildrenAnswers( answers );
    AddLabel( "Seq" );
    ++lastVisited;
}

void IRT::PrintVisitor::Visit( const IRT::CStatementList &statement ) {
    std::vector<const IRT::INode *> children;
    for ( int i = 0; i < statement.Statements( ).size( ); ++i ) {
        children.push_back( statement.Statements( )[ i ].get( ));
    }
    ChildrenAnswers answers = VisitChildren( children );

    AddChildrenAnswers( answers );
    AddLabel( "StatementList" );
    ++lastVisited;
}

std::string IRT::PrintVisitor::GetResult( ) {
    return "digraph G{\ngraph[ordering=\"out\"];\n" + description + "}\n";
}

IRT::PrintVisitor::PrintVisitor( ) {
    lastVisited = 0;
}

IRT::ChildrenAnswers IRT::PrintVisitor::VisitChildren( std::vector<const INode *> children ) {
    ChildrenAnswers answers = ChildrenAnswers( );
    for ( int i = 0; i < children.size( ); i++ ) {
        if ( children[ i ] ) {
            children[ i ]->Accept( *this );
            answers.PushBack( this->description, lastVisited );
            this->description = "";
        }
    }
    return answers;
}

void IRT::PrintVisitor::AddChildrenDescriptions( IRT::ChildrenAnswers answers ) {
    for ( int i = 0; i < answers.descriptions.size( ); i++ ) {
        this->description += answers.descriptions[ i ];
    }
}

void IRT::PrintVisitor::AddChildrenIds( IRT::ChildrenAnswers answers ) {
    for ( int i = 0; i < answers.descriptions.size( ); i++ ) {
        AddArrow( answers.ids[ i ] );
    }
}

void IRT::PrintVisitor::AddChildrenAnswers( IRT::ChildrenAnswers answers ) {
    this->description = "";
    AddChildrenDescriptions( answers );
    AddChildrenIds( answers );
}

std::string IRT::PrintVisitor::ConstructLabel( std::string label, int id ) {
    return "\t" + std::to_string( id ) + "[label=\"" + label + "\"]\n";
}

void IRT::PrintVisitor::AddLabel( std::string label ) {
    this->description += ConstructLabel( label, lastVisited + 1 );
}

void IRT::PrintVisitor::AddArrow( int child_id ) {
    this->description += "\t" + std::to_string( lastVisited + 1 ) + " -> " + std::to_string( child_id ) + "\n";
}

void IRT::ChildrenAnswers::PushBack( std::string description, int id ) {
    this->descriptions.push_back( description );
    this->ids.push_back( id );
}

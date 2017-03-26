//
// Created by izeren on 3/4/17.
//

#include "../../shared_ptrs_nodes/Expressions.h"
#include "CBuildVisitor.h"
#include "../../bison.hpp"
#include <list>
#include <set>

void CBuildVisitor::Visit( CIdExp &expression ) {
    const IRT::IAddress *address = currentFrame->GetAddress( expression.name );
    if( address ) {
        std::shared_ptr<const ClassInfo> classDefinition = symbolTable->classes[currentFrame->GetClassName()];
        auto varInfoIt = classDefinition->fields->variables.find( expression.name );

        updateSubtreeWrapper( new IRT::CExpressionWrapper(
                std::move( address->ToExpression())
        ));

    }
}

void CBuildVisitor::Visit( CIdPtrExp &exp ) {
    assert( false );
}

void CBuildVisitor::Visit( CNumExp &expression ) {
    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CConstExpression( expression.number )
    ));
}

void CBuildVisitor::Visit( COpExp &expression ) {
    expression.leftOperand->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperLeft = std::move( wrapper );

    expression.rightOperand->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperRight = std::move( wrapper );

    IRT::enums::TOperationType operatorType = operatorAst2Irt( expression.operation );

    std::unique_ptr<const IRT::CExpression> binOpPtr = std::unique_ptr<const IRT::CExpression>(
            new IRT::CBinopExpression(
                    std::move( wrapperLeft->ToExpression()),
                    std::move( wrapperRight->ToExpression()),
                    operatorType ));
    updateSubtreeWrapper( new IRT::CExpressionWrapper( std::move( binOpPtr )));
}

void CBuildVisitor::Visit( CLogExp &expression ) {
    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CConstExpression( expression.variable ? 1 : 0 )
    ));
}

void CBuildVisitor::Visit( CLogOpExp &expression ) {
    expression.leftOperand->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperLeft = std::move( wrapper );

    expression.rightOperand->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperRight = std::move( wrapper );

    if( expression.operation == enums::TLogicalOperation::AND ) {
        updateSubtreeWrapper( new IRT::CAndConditionalWrapper(
                std::move( wrapperLeft ),
                std::move( wrapperRight )
        ));
    } else if( expression.operation == enums::TLogicalOperation::OR ) {
        updateSubtreeWrapper( new IRT::COrConditionalWrapper(
                std::move( wrapperLeft ),
                std::move( wrapperRight )
        ));
    }
}

void CBuildVisitor::Visit( CCompExp &expression ) {
    expression.leftOperand->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperLeft = std::move( wrapper );

    expression.rightOperand->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperRight = std::move( wrapper );

    if( expression.operation == enums::TCompareOperation::LESS ) {
        updateSubtreeWrapper( new IRT::CRelativeConditionalWrapper(
                IRT::enums::TLogicOperator::LESS,
                std::move( wrapperLeft->ToExpression()),
                std::move( wrapperRight->ToExpression())
        ));
    }
}

void CBuildVisitor::Visit( CUnarMinusExp &expression ) {
    expression.rightOperand->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperRight = std::move( wrapper );

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CBinopExpression( new IRT::CConstExpression( 0 ),
                                       std::move( wrapperRight->ToExpression()), IRT::enums::TOperationType::MINUS )
    ));
}

void CBuildVisitor::Visit( CGetLengthExp &expression ) {
    expression.array->lengthExpression->Accept( *this );
    std::unique_ptr<const IRT::CExpression> targetExpression = std::move( wrapper->ToExpression());

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( targetExpression )
    ));

}

void CBuildVisitor::Visit( CGetFieldExp &exp ) {
    const IRT::IAddress *address = currentFrame->GetAddress( exp.field->id->name );
    if( address ) {
        updateSubtreeWrapper( new IRT::CExpressionWrapper(
                std::move( address->ToExpression())
        ));
    }

}

void CBuildVisitor::Visit( CCallMethodExp &expression ) {

    IRT::CExpressionList *expressionListIrt = new IRT::CExpressionList();
    std::vector<std::unique_ptr<IExpression> > &arguments = expression.args->exps;
    for( auto it = arguments.begin(); it != arguments.end(); ++it ) {
        (*it)->Accept( *this );
        expressionListIrt->Add( std::move( wrapper->ToExpression()));
    }
    std::string callerName;
    if( expression.classOwner ) {
        callerName = expression.classOwner->name;
    } else {
        callerName = currentClassName;
    }
    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CCallExpression(
                    new IRT::CNameExpression(
                            IRT::CLabel( GetMethodFullName( callerName, expression.methodName->name ))
                    ),
                    expressionListIrt
            )
    ));

}

void CBuildVisitor::Visit( CExpList &exp ) {
//    Expression list is manually proceeded in CCallMethod
    assert( false );
}

void CBuildVisitor::Visit( CNegativeExpression &expression ) {
    expression.expression->Accept( *this );

    updateSubtreeWrapper( new IRT::CNegateConditionalWrapper(
            std::move( wrapper )
    ));
}

void CBuildVisitor::Visit( CArrayExpression &expression ) {
    expression.lengthExpression->Accept( *this );

    std::unique_ptr<const IRT::CExpression> expressionLength = std::move( wrapper->ToExpression());

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( currentFrame->ExternalCall(
                    "malloc",
                    std::move( std::unique_ptr<const IRT::CExpressionList>(
                            new IRT::CExpressionList(
                                    new IRT::CBinopExpression(
                                            new IRT::CBinopExpression(
                                                    std::move( expressionLength ),
                                                    std::move( std::unique_ptr<const IRT::CExpression>(
                                                            new IRT::CConstExpression( 1 ))),
                                                    IRT::enums::TOperationType::PLUS
                                            ),
                                            new IRT::CConstExpression( currentFrame->GetWordSize()),
                                            IRT::enums::TOperationType::MULTYPLY
                                    )
                            )
                    ))
            ))
    ));
}

void CBuildVisitor::Visit( CThisExpression &exp ) {
    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( currentFrame->GetThisAddress()->ToExpression())
    ));
}

void CBuildVisitor::Visit( CByIndexExpression &expression ) {
    expression.identifier->Accept( *this );
    std::unique_ptr<const IRT::CExpression> containerExpression = std::move( wrapper->ToExpression());

    expression.indexExpression->Accept( *this );
    std::unique_ptr<const IRT::CExpression> indexExpression = std::move( wrapper->ToExpression());

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CMemExpression(
                    new IRT::CBinopExpression(
                            std::move( containerExpression ),
                            std::move( std::unique_ptr<const IRT::CExpression>(
                                    new IRT::CBinopExpression(
                                            new IRT::CBinopExpression(
                                                    std::move( indexExpression ),
                                                    std::move( std::unique_ptr<const IRT::CExpression>(
                                                            new IRT::CConstExpression( 1 )
                                                    )),
                                                    IRT::enums::TOperationType::PLUS
                                            ),
                                            new IRT::CConstExpression( currentFrame->GetWordSize()),
                                            IRT::enums::TOperationType::MULTYPLY
                                    )
                            )),
                            IRT::enums::TOperationType::PLUS
                    )
            )
    ));
}

void CBuildVisitor::Visit( CNewIdentifier &expression ) {
    std::shared_ptr<const ClassInfo> classDefinition = symbolTable->classes[expression.identifier->name];
    int fieldCount = static_cast<int>(classDefinition->fields->variableNames.size());

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( currentFrame->ExternalCall(
                    "malloc",
                    std::move( std::unique_ptr<const IRT::CExpressionList>(
                            new IRT::CExpressionList(
                                    new IRT::CBinopExpression(
                                            new IRT::CConstExpression( fieldCount ),
                                            new IRT::CConstExpression( currentFrame->GetWordSize()),
                                            IRT::enums::TOperationType::MULTYPLY
                                    )
                            )
                    ))
            ))
    ));

}

void CBuildVisitor::Visit( CAssignStm &statement ) {
    statement.leftExpression->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperLeftPart = std::move( wrapper );
    statement.rightExpression->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperRightPart = std::move( wrapper );

    updateSubtreeWrapper( new IRT::CStatementWrapper(
            new IRT::CMoveStatement(
                    std::move( wrapperLeftPart->ToExpression()),
                    std::move( wrapperRightPart->ToExpression())
            )
    ));
}

void CBuildVisitor::Visit( CAssignSubscriptStm &statement ) {
    statement.idExpression->Accept( *this );
    std::unique_ptr<const IRT::CExpression> leftPartExpression = std::move( wrapper->ToExpression());

    statement.valueExpression->Accept( *this );
    std::unique_ptr<const IRT::CExpression> rightPartExpression = std::move( wrapper->ToExpression());

    std::unique_ptr<const IRT::CExpression> indexExpression = new IRT::CConstExpression( statement.offset->number );

    updateSubtreeWrapper( new IRT::CStatementWrapper(
            new IRT::CMoveStatement(
                    std::move( std::unique_ptr<const IRT::CExpression>(
                            new IRT::CMemExpression(
                                    new IRT::CBinopExpression(
                                            std::move( leftPartExpression ),
                                            std::move( std::unique_ptr<const IRT::CExpression>(
                                                    new IRT::CBinopExpression(
                                                            new IRT::CBinopExpression(
                                                                    std::move( indexExpression ),
                                                                    std::move( std::unique_ptr<const IRT::CExpression>(
                                                                            new IRT::CConstExpression( 1 )
                                                                    )),
                                                                    IRT::enums::TOperationType::PLUS
                                                            ),
                                                            new IRT::CConstExpression( currentFrame->GetWordSize()),
                                                            IRT::enums::TOperationType::MULTYPLY
                                                    )
                                            )),
                                            IRT::enums::TOperationType::PLUS
                                    )
                            )
                    )),
                    std::move( rightPartExpression )
            )
    ));

}

void CBuildVisitor::Visit( CCompoundStm &statement ) {
    if( statement.leftStatement == NULL ) {
        updateSubtreeWrapper( NULL );
    } else {
        statement.leftStatement->Accept( *this );
        auto leftStatement = std::move( wrapper );
        statement.rightStatement->Accept( *this );

        if( wrapper ) {
            std::unique_ptr<const IRT::CStatement> rightStatement = std::move( wrapper->ToStatement());
            updateSubtreeWrapper( new IRT::CSeqStatement( std::move( leftStatement->ToStatement()), rightStatement ));
        } else {
            updateSubtreeWrapper( leftStatement );
        }
    }
}


void CBuildVisitor::Visit( CPrintStm &statement ) {
    statement.expression->Accept( *this );

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( currentFrame->ExternalCall(
                    "print",
                    std::move( std::unique_ptr<const IRT::CExpressionList>(
                            new IRT::CExpressionList( std::move( wrapper->ToExpression()))
                    ))
            ))
    ));
}

void CBuildVisitor::Visit( CSimpleStm &statement ) {
//    Old dummy class (not used)
    assert( false );
}

void CBuildVisitor::Visit( CIfStm &statement ) {
    statement.conditionExpression->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperCondition = std::move( wrapper );
    statement.positiveStatement->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperTargetPositive = std::move( wrapper );
    statement.negativeStatement->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperTargetNegative = std::move( wrapper );

    IRT::CLabel labelTrue;
    IRT::CLabel labelFalse;
    IRT::CLabel labelJoin;

    IRT::CLabel *resultLabelTrue = &labelJoin;
    IRT::CLabel *resultLabelFalse = &labelJoin;

    std::unique_ptr<const IRT::CStatement> suffix( new IRT::CLabelStatement( labelJoin ));
    if( wrapperTargetNegative ) {
        resultLabelFalse = &labelFalse;

        suffix = std::move( std::unique_ptr<const IRT::CStatement>(
                new IRT::CSeqStatement(
                        new IRT::CLabelStatement( labelFalse ),
                        new IRT::CSeqStatement(
                                std::move( wrapperTargetNegative->ToStatement()),
                                std::move( suffix )
                        )
                )
        ));
        if( wrapperTargetPositive ) {
            suffix = std::move( std::unique_ptr<const IRT::CStatement>(
                    new IRT::CSeqStatement(
                            std::move( std::unique_ptr<const IRT::CStatement>(
                                    new IRT::CJumpStatement( labelJoin )
                            )),
                            std::move( suffix )
                    )
            ));
        }
    }

    if( wrapperTargetPositive ) {
        resultLabelTrue = &labelTrue;

        suffix = std::move( std::unique_ptr<const IRT::CStatement>(
                new IRT::CSeqStatement(
                        new IRT::CLabelStatement( labelTrue ),
                        new IRT::CSeqStatement(
                                std::move( wrapperTargetPositive->ToStatement()),
                                std::move( suffix )
                        )
                )
        ));
    }

    updateSubtreeWrapper( new IRT::CStatementWrapper(
            new IRT::CSeqStatement(
                    std::move( wrapperCondition->ToConditional( *resultLabelTrue, *resultLabelFalse )),
                    std::move( suffix )
            )
    ));
}


void CBuildVisitor::Visit( CWhileStm &statement ) {

    statement.conditionExpression->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperCondition = std::move( wrapper );
    statement.statement->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperBody = std::move( wrapper );

    IRT::CLabel labelLoop;
    IRT::CLabel labelBody;
    IRT::CLabel labelDone;

    std::unique_ptr<const IRT::CStatement> suffix(
            new IRT::CSeqStatement(
                    new IRT::CJumpStatement( labelLoop ),
                    new IRT::CLabelStatement( labelDone )
            )
    );
    if( wrapperBody ) {
        suffix = std::move( std::unique_ptr<const IRT::CStatement>(
                new IRT::CSeqStatement(
                        std::move( wrapperBody->ToStatement()),
                        std::move( suffix )
                )
        ));
    }

    updateSubtreeWrapper( new IRT::CStatementWrapper(
            new IRT::CSeqStatement(
                    new IRT::CLabelStatement( labelLoop ),
                    new IRT::CSeqStatement(
                            std::move( wrapperCondition->ToConditional( labelBody, labelDone )),
                            std::move( std::unique_ptr<const IRT::CStatement>(
                                    new IRT::CSeqStatement(
                                            std::move( std::unique_ptr<const IRT::CStatement>(
                                                    new IRT::CLabelStatement( labelBody )
                                            )),
                                            std::move( suffix )
                                    )
                            ))
                    )
            )
    ));

}

void CBuildVisitor::Visit( CType &stm ) {
//    Should never be called
    assert( false );
}

void CBuildVisitor::Visit( CField &statement ) {
//    Should never be called
    assert( false );
}

void CBuildVisitor::Visit( CFieldList &stm ) {
//    Should never be called
    assert( false );
}

void CBuildVisitor::Visit( CArgument &stm ) {
//    Should never be called
    assert( false );
}

//
void CBuildVisitor::Visit( CArgumentList &stm ) {
//    Should never be called
    assert( false );
}

void CBuildVisitor::Visit( CMethod &statement ) {

    buildNewFrame( &statement );
    std::string methodFullName = GetMethodFullName( currentFrame->GetClassName(), currentFrame->GetMethodName());

    statement.statements->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> statementListWrapper = std::move( wrapper );

    statement.returnExp->Accept( *this );
    std::unique_ptr<const IRT::CExpression> expressionReturn = std::move( wrapper->ToExpression());

    if( statementListWrapper ) {
        updateSubtreeWrapper( new IRT::CStatementWrapper(
                new IRT::CSeqStatement(
                        new IRT::CLabelStatement( IRT::CLabel( methodFullName )),
                        new IRT::CSeqStatement(
                                std::move( statementListWrapper->ToStatement()),
                                std::move( std::unique_ptr<const IRT::CStatement>(
                                        new IRT::CMoveStatement(
                                                std::move( currentFrame->GetReturnValueAddress()->ToExpression()),
                                                std::move( expressionReturn )
                                        )
                                ))
                        )
                )
        ));
    } else {
        updateSubtreeWrapper( new IRT::CStatementWrapper(
                new IRT::CSeqStatement(
                        new IRT::CLabelStatement( IRT::CLabel( methodFullName )),
                        new IRT::CMoveStatement(
                                std::move( currentFrame->GetReturnValueAddress()->ToExpression()),
                                std::move( expressionReturn )
                        )
                )
        ));
    }
}

void CBuildVisitor::Visit( CMethodList &stm ) {
//    Should never be called
    assert( false );
}

void CBuildVisitor::Visit( CClass &statement ) {
    currentClassName = statement.id->name;
    auto methodDeclarations = statement.methods->methods;
    for( auto it = methodDeclarations.begin(); it != methodDeclarations.end(); ++it ) {
        (*it)->Accept( *this );
    }
}

void CBuildVisitor::Visit( CClassList &stm ) {
//    Should never be called
    assert( false );
}

void CBuildVisitor::Visit( CMainMethod &stm ) {
//    Should never be called
    assert( false );
}

void CBuildVisitor::Visit( CMainClass &statement ) {
    buildNewFrame( &statement );
    std::string methodFullName = GetMethodFullName( currentFrame->GetClassName(), currentFrame->GetMethodName() );

    statement.mainMethod->statements->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> statementListWrapper = std::move( wrapper );
    if ( statementListWrapper ) {
        updateSubtreeWrapper( new IRT::CStatementWrapper(
                new IRT::CSeqStatement(
                        std::move( std::unique_ptr<const IRT::CStatement>(
                                new IRT::CLabelStatement( IRT::CLabel( methodFullName ) )
                        ) ),
                        std::move( statementListWrapper->ToStatement() )
                )
        ) );
    } else {
        // empty function
        updateSubtreeWrapper( new IRT::CStatementWrapper(
                new IRT::CLabelStatement( IRT::CLabel( methodFullName ) )
        ) );
    }

    treesOfMethods->emplace( methodFullName, std::move( wrapper->ToStatement() ) );
}

void CBuildVisitor::Visit( CProgram &statement ) {
    statement.mainClass->Accept( *this );
    auto classDeclarations = statement.classList->classes;
    for( auto it = classDeclarations.begin(); it != classDeclarations.end(); ++it ) {
        (*it)->Accept( *this );
    }
}

std::unique_ptr<const MethodToIRTMap> CBuildVisitor::GetMethodFromIrtMap() {
    return std::unique_ptr<const MethodToIRTMap>();
}

IRT::enums::TOperationType CBuildVisitor::operatorAst2Irt( enums::TOperation type ) const {
    IRT::enums::TOperationType typeResult;
    switch( type ) {
        case enums::TOperation::PLUS:
            typeResult = IRT::enums::TOperationType::PLUS;
            break;
        case enums::TOperation::MINUS:
            typeResult = IRT::enums::TOperationType::MINUS;
            break;
        case enums::TOperation::MULTIPLY:
            typeResult = IRT::enums::TOperationType::MULTYPLY;
            break;
        case enums::TOperation::MOD:
            typeResult = IRT::enums::TOperationType::MOD;
            break;
        default: {
            // basic assert
            assert( false );
        }
    }
    return typeResult;
}

IRT::enums::TOperationType CBuildVisitor::logOperatorAst2Irt( enums::TLogicalOperation type ) const {
    IRT::enums::TOperationType typeResult;
    switch( type ) {
        case enums::TLogicalOperation::AND:
            typeResult = IRT::enums::TOperationType::AND;
            break;
        case enums::TLogicalOperation::OR:
            typeResult = IRT::enums::TOperationType::OR;
            break;
        default: {
            // basic assert
            assert( false );
        }
    }
    return typeResult;
}

void CBuildVisitor::updateSubtreeWrapper( IRT::ISubtreeWrapper *_wrapper ) {
    wrapper = std::unique_ptr<IRT::ISubtreeWrapper>( _wrapper );
}

void CBuildVisitor::updateSubtreeWrapper( std::unique_ptr<IRT::ISubtreeWrapper> _wrapper ) {
    wrapper = std::move( _wrapper );
}

std::string CBuildVisitor::GetMethodFullName( const std::string &className, const std::string &methodName ) {
    return className + "::" + methodName;
}

namespace {
    template<class InputIteratorArguments, class InputIteratorLocals, class InputIteratorFields>
    void CBuildVisitor::buildNewFrame( const std::string &className, const std::string &methodName,
                                       InputIteratorArguments argumentsLeftIt, InputIteratorArguments argumentsRightIt,
                                       InputIteratorLocals localsLeftIt, InputIteratorLocals localsRightIt,
                                       InputIteratorFields fieldsLeftIt, InputIteratorFields fieldsRightIt ) {
        std::unique_ptr<IRT::CFrame> newFrame = std::unique_ptr<IRT::CFrame>( new IRT::CFrame( className, methodName ));

        currentFrame = newFrame.get();

        currentFrame->AddThisAddress();
        for( auto it = fieldsLeftIt; it != fieldsRightIt; ++it ) {
            currentFrame->AddFieldAddress( *it );
        }
        // arguments and locals overwrite class fields in the scope
        for( auto it = argumentsLeftIt; it != argumentsRightIt; ++it ) {
            currentFrame->AddArgumentAddress( *it );
        }
        currentFrame->AddReturnAddress();
        for( auto it = localsLeftIt; it != localsRightIt; ++it ) {
            currentFrame->AddLocalAddress( *it );
        }

        std::string methodFullName = GetMethodFullName( className, methodName );
        frames.emplace( methodFullName, std::move( newFrame ));
    }
}

void CBuildVisitor::buildNewFrame( const CMethod *declaration ) {
    std::shared_ptr<const ClassInfo> classDefinition = symbolTable->classes[currentClassName];
    std::shared_ptr<const MethodInfo> methodDefinition = classDefinition->methods[declaration->name->name];

    const std::vector<std::unique_ptr<CArgument>> &arguments = declaration->arguments->arguments;
    std::vector<std::string> argumentsNames;
    argumentsNames.reserve( arguments.size());
    for( auto it : arguments ) {
        argumentsNames.push_back( it->id->name );
    }
    auto localNames = methodDefinition->fields->variableNames;

    auto fieldsNames = std::list<std::string>();
    std::shared_ptr<const ClassInfo> baseClass = classDefinition;
    while( baseClass ) {
        auto fields = baseClass->fields->variableNames;
        for( auto name : fields ) {
            fieldsNames.push_back( name );
        }
        baseClass = baseClass->baseClass != "" ? symbolTable->classes[baseClass->baseClass] : nullptr;
    }

    buildNewFrame( currentClassName, declaration->name->name, argumentsNames.begin(), argumentsNames.end(),
                   localNames.begin(), localNames.end(), fieldsNames.begin(), fieldsNames.end());
}

void CBuildVisitor::buildNewFrame( const CMainClass *mainClass ) {
    std::list<std::string> emptySet;
    buildNewFrame( mainClass->id->name, "main", emptySet.end(), emptySet.end(),
                   emptySet.end(), emptySet.end(), emptySet.end(), emptySet.end());
}



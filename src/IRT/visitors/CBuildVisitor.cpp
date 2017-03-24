//
// Created by izeren on 3/4/17.
//

#include "../../shared_ptrs_nodes/Expressions.h"
#include "CBuildVisitor.h"
#include "../../bison.hpp"
#include <list>

void CBuildVisitor::Visit( CIdExp &expression ) {
    const IRT::IAddress *address = currentFrame->GetAddress( expression.name );
    if( address ) {
        std::shared_ptr<const ClassInfo> classDefinition = symbolTable->classes[currentFrame->GetClassName()];
        auto varInfoIt = classDefinition->fields->variables.find( expression.name );

        if( varInfoIt != classDefinition->fields->variables.end()) {
            auto type = varInfoIt->second->type;
            if( !type->isPrimitive ) {
                nameOfMethodParentClass = type->className;
            }
        }

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
        nameOfMethodParentClass = exp.classOwner->id->name;
        updateSubtreeWrapper( new IRT::CExpressionWrapper(
                std::move( address->ToExpression())
        ));
    }

}

void CBuildVisitor::Visit( CCallMethodExp &expression ) {

    std::string methodCaller = nameOfMethodParentClass;

    IRT::CExpressionList *expressionListIrt = new IRT::CExpressionList();
    std::vector<std::unique_ptr<IExpression> > &arguments = expression.args->exps;
    for( auto it = arguments.begin(); it != arguments.end(); ++it ) {
        (*it)->Accept( *this );
        expressionListIrt->Add( std::move( wrapper->ToExpression()));
    }

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CCallExpression(
                    new IRT::CNameExpression(
                            IRT::CLabel( GetMethodFullName( methodCaller, expression.methodName->name ))
                    ),
                    expressionListIrt
            )
    ));

    std::shared_ptr<ClassInfo> classDefinition = symbolTable->classes[methodCaller];
    std::shared_ptr<MethodInfo> methodDefinition = symbolTable->FindMethodDefinition( expression.methodName->name,
                                                                                      classDefinition );
    CType type = methodDefinition->returnType->type;
    if( !type.isPrimitive ) {
        nameOfMethodParentClass = type.name->name;
    }

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
    nameOfMethodParentClass = currentClassName;
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

    nameOfMethodParentClass = expression.identifier->name;
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
        updateSubtreeWrapper( new IRT::CSeqStatement(
                new IRT::CLabelStatement( IRT::CLabel( "Fake" )),
                new IRT::CLabelStatement( IRT::CLabel( "Fake" ))
        ));
    } else {
        statement.leftStatement->Accept( *this );
        std::unique_ptr<const IRT::CStatement> leftStatement = std::move( wrapper->ToStatement());
        statement.rightStatement->Accept( *this );
        std::unique_ptr<const IRT::CStatement> rightStatement = std::move( wrapper->ToStatement());
        updateSubtreeWrapper( new IRT::CSeqStatement( leftStatement, rightStatement ));
    }
}

//
//void CBuildVisitor::Visit( CPrintStm &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CSimpleStm &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CIfStm &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CWhileStm &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CType &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CField &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CFieldList &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CArgument &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CArgumentList &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CMethod &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CMethodList &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CClass &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CClassList &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CMainMethod &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CMainClass &stm ) {
//
//}
//
//void CBuildVisitor::Visit( CProgram &stm ) {
//
//}

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



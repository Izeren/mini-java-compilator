//
// Created by izeren on 3/4/17.
//

#include "../../shared_ptrs_nodes/Expressions.h"
#include "CBuildVisitor.h"
#include "../../bison.hpp"
#include "../../symbol_table/CConstructSymbolTableVisitor.h"
#include <list>
#include <set>
#include "../utils/symbol_table_utils.h"

void CBuildVisitor::Visit( CIdExp &expression ) {
    std::cout << "IRT builder: CIdExp\n";
    const IRT::IAddress *address = currentFrame->GetLocalVisibilityAddress(expression.name);

    assert(address != NULL);

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( address->ToExpression())
    ));

    auto varInfo = getVariableInfoFromLocalArgAndFields(symbolTable, currentClassName, currentMethod, expression.name);
    if (varInfo->type->isPrimitive) {
        currentObjectClassName = "";
    } else {
        currentObjectClassName = varInfo->type->className;
    }
}

void CBuildVisitor::Visit( CIdPtrExp &exp ) {
    std::cout << "IRT builder: CIdPtrExp\n";
    assert( false );
}

void CBuildVisitor::Visit( CNumExp &expression ) {
    std::cout << "IRT builder: CNumExp\n";
    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CConstExpression( expression.number )
    ));

    currentObjectClassName = "";
}

void CBuildVisitor::Visit( COpExp &expression ) {
    std::cout << "IRT builder: COpExp\n";
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
    std::cout << "IRT builder: CLogExp\n";
    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CConstExpression( expression.variable ? 1 : 0 )
    ));
}

void CBuildVisitor::Visit( CLogOpExp &expression ) {
    std::cout << "IRT builder: CLogOpExp\n";
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
    std::cout << "IRT builder: CCompExp\n";
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
    std::cout << "IRT builder: CUnarMinusExp\n";
    expression.rightOperand->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperRight = std::move( wrapper );

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CBinopExpression( std::unique_ptr<const IRT::CExpression>( new IRT::CConstExpression( 0 )),
                                       std::move( wrapperRight->ToExpression()), IRT::enums::TOperationType::MINUS )
    ));
}

void CBuildVisitor::Visit( CGetLengthExp &expression ) {
    std::cout << "IRT builder: CGetLength\n";
    expression.arrayIdentifier->Accept( *this );
    std::unique_ptr<const IRT::CExpression> containerExpression = std::move( wrapper->ToExpression());

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CMemExpression(
                    std::move( std::unique_ptr<const IRT::CExpression>( new IRT::CBinopExpression(
                            std::move( containerExpression ),
                            std::move( std::unique_ptr<const IRT::CExpression>(new IRT::CConstExpression( 0 ))),
                            IRT::enums::TOperationType::PLUS
                                                                        )
                    )))
    ));

}

void CBuildVisitor::Visit( CCallMethodExp &expression ) {

    std::cout << "IRT builder: CCallMethod\n";

    expression.objectExpression->Accept( *this );
    std::string mineMethodObjectClassName = currentObjectClassName;
    assert(mineMethodObjectClassName != "");

    IRT::CExpressionList *expressionListIrt = new IRT::CExpressionList();
    std::vector<std::unique_ptr<IExpression> > &arguments = expression.args->exps;
    for( auto it = arguments.begin(); it != arguments.end(); ++it ) {
        (*it)->Accept( *this );
        expressionListIrt->Add( std::move( wrapper->ToExpression()));
    }

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CCallExpression(
                    std::unique_ptr<const IRT::CExpression>( new IRT::CNameExpression(
                            IRT::CLabel( GetMethodFullName( mineMethodObjectClassName, expression.methodName->name ))
                    )),
                    std::unique_ptr<const IRT::CExpressionList>( expressionListIrt ))
    ));

    std::shared_ptr<ClassInfo> classInfo = symbolTable->classes.at(mineMethodObjectClassName);
    auto methodInfo = classInfo->methods[expression.methodName->name];
    auto returnTypeInfo = methodInfo->returnType;
    if (returnTypeInfo->isPrimitive) {
        currentObjectClassName = "";
    } else {
        currentObjectClassName = returnTypeInfo->className;
    }
}

void CBuildVisitor::Visit( CExpList &exp ) {
//    Expression list is manually proceeded in CCallMethod
    std::cout << "IRT builder: CExpList\n";
    assert( false );
}

void CBuildVisitor::Visit( CNegativeExpression &expression ) {
    std::cout << "IRT builder: CNegativeExpression\n";
    expression.expression->Accept( *this );

    updateSubtreeWrapper( new IRT::CNegateConditionalWrapper(
            std::move( wrapper )
    ));
}

void CBuildVisitor::Visit( CNewArrayExpression &expression ) {
    std::cout << "IRT builder: CNewArrayExpression\n";
    expression.lengthExpression->Accept( *this );

    std::unique_ptr<const IRT::CExpression> expressionLength = std::move( wrapper->ToExpression());

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( currentFrame->ExternalCall(
                    "malloc",
                    std::move( std::unique_ptr<const IRT::CExpressionList>(
                            new IRT::CExpressionList(
                                    std::unique_ptr<const IRT::CExpression>( new IRT::CBinopExpression(
                                            std::unique_ptr<const IRT::CExpression>( new IRT::CBinopExpression(
                                                    std::unique_ptr<const IRT::CExpression>(
                                                            std::move( expressionLength )),
                                                    std::move( std::unique_ptr<const IRT::CExpression>(
                                                            new IRT::CConstExpression( 1 ))),
                                                    IRT::enums::TOperationType::PLUS
                                            )),
                                            std::unique_ptr<const IRT::CExpression>(
                                                    new IRT::CConstExpression( currentFrame->GetWordSize())),
                                            IRT::enums::TOperationType::MULTYPLY
                                    ))
                            )
                    ))
            ))
    ));
}

void CBuildVisitor::Visit( CByIndexExpression &expression ) {
    std::cout << "IRT builder: CByIndexExpression\n";
    expression.identifier->Accept( *this );
    std::unique_ptr<const IRT::CExpression> containerExpression = std::move( wrapper->ToExpression());

    expression.indexExpression->Accept( *this );
    std::unique_ptr<const IRT::CExpression> indexExpression = std::move( wrapper->ToExpression());

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            new IRT::CMemExpression(
                    std::move( std::unique_ptr<const IRT::CExpression>( new IRT::CBinopExpression(
                            std::move( containerExpression ),
                            std::move( std::unique_ptr<const IRT::CExpression>(
                                    new IRT::CBinopExpression(
                                            std::move(
                                                    std::unique_ptr<const IRT::CExpression>( new IRT::CBinopExpression(
                                                            std::move( indexExpression ),
                                                            std::move( std::unique_ptr<const IRT::CExpression>(
                                                                    new IRT::CConstExpression( 1 )
                                                            )),
                                                            IRT::enums::TOperationType::PLUS
                                                    ))),
                                            std::unique_ptr<const IRT::CExpression>(
                                                    new IRT::CConstExpression( currentFrame->GetWordSize())),
                                            IRT::enums::TOperationType::MULTYPLY
                                    )
                            )),
                            IRT::enums::TOperationType::PLUS
                                                                        )
                    )))
    ));
}

void CBuildVisitor::Visit( CNewIdentifier &expression ) {
    std::cout << "IRT builder: CNewIdentifier\n";
    int fieldCount = getFieldCountWithSuper(symbolTable, expression.identifier->name);

    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( currentFrame->ExternalCall(
                    "malloc",
                    std::move( std::unique_ptr<const IRT::CExpressionList>(
                            new IRT::CExpressionList(
                                    std::move( std::unique_ptr<const IRT::CExpression>( new IRT::CBinopExpression(
                                            std::move( std::unique_ptr<const IRT::CExpression>(
                                                    new IRT::CConstExpression( fieldCount ))),
                                            std::move( std::unique_ptr<const IRT::CExpression>(
                                                    new IRT::CConstExpression( currentFrame->GetWordSize()))),
                                            IRT::enums::TOperationType::MULTYPLY
                                    )))
                            )
                    ))
            ))
    ));

    currentObjectClassName = expression.identifier->name;
}

void CBuildVisitor::Visit( CAssignStm &statement ) {
    std::cout << "IRT builder: CAssign\n";
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
    std::cout << "IRT builder: CAssignSubscriptStm\n";
    statement.idExpression->Accept( *this );
    std::unique_ptr<const IRT::CExpression> leftPartExpression = std::move( wrapper->ToExpression());

    statement.valueExpression->Accept( *this );
    std::unique_ptr<const IRT::CExpression> rightPartExpression = std::move( wrapper->ToExpression());

    std::unique_ptr<const IRT::CExpression> indexExpression = std::move( std::unique_ptr<const IRT::CExpression>(
            new IRT::CConstExpression( statement.offset->number )));

    updateSubtreeWrapper( new IRT::CStatementWrapper(
            new IRT::CMoveStatement(
                    std::move( std::unique_ptr<const IRT::CExpression>(
                            new IRT::CMemExpression(
                                    std::move( std::unique_ptr<const IRT::CExpression>( new IRT::CBinopExpression(
                                            std::move( leftPartExpression ),
                                            std::move( std::unique_ptr<const IRT::CExpression>(
                                                    new IRT::CBinopExpression(
                                                            std::move( std::unique_ptr<const IRT::CExpression>(
                                                                    new IRT::CBinopExpression(
                                                                            std::move( indexExpression ),
                                                                            std::move(
                                                                                    std::unique_ptr<const IRT::CExpression>(
                                                                                            new IRT::CConstExpression(
                                                                                                    1 )
                                                                                    )),
                                                                            IRT::enums::TOperationType::PLUS
                                                                    ))),
                                                            std::move( std::unique_ptr<const IRT::CExpression>(
                                                                    new IRT::CConstExpression(
                                                                            currentFrame->GetWordSize()))),
                                                            IRT::enums::TOperationType::MULTYPLY
                                                    )
                                            )),
                                            IRT::enums::TOperationType::PLUS
                                                                                        )
                                               )
                                    )))),
                    std::move( rightPartExpression )
            )
    ));

}

void CBuildVisitor::Visit( CCompoundStm &statement ) {
    std::cout << "IRT builder: CCompound\n";
    if( statement.leftStatement == NULL ) {
        updateSubtreeWrapper( NULL );
    } else {
        statement.leftStatement->Accept( *this );
        auto leftStatement = std::move( wrapper );
        statement.rightStatement->Accept( *this );

        if( wrapper ) {
            std::unique_ptr<const IRT::CStatement> rightStatement = std::move( wrapper->ToStatement());
            std::unique_ptr<const IRT::CStatement> compound = std::move( std::unique_ptr<const IRT::CStatement>(
                    new IRT::CSeqStatement( std::move( leftStatement->ToStatement()), std::move( rightStatement ))));
            updateSubtreeWrapper( new IRT::CStatementWrapper( std::move( compound )));
        } else {
            updateSubtreeWrapper( new IRT::CStatementWrapper( std::move( leftStatement->ToStatement())));
        }
    }
}


void CBuildVisitor::Visit( CPrintStm &statement ) {
    std::cout << "IRT builder: CPrintStm\n";
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

void CBuildVisitor::Visit( CIfStm &statement ) {
    std::cout << "IRT builder: CIfStm\n";
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
                        std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CLabelStatement( labelFalse ))),
                        std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CSeqStatement(
                                std::move( wrapperTargetNegative->ToStatement()),
                                std::move( suffix )
                        )))
                )
        ));
        if( wrapperTargetPositive ) {
            suffix = std::move( std::unique_ptr<const IRT::CStatement>(
                    new IRT::CSeqStatement(
                            std::move( std::unique_ptr<const IRT::CStatement>(
                                    new IRT::CJumpStatement( std::move(std::unique_ptr<const IRT::CLabelStatement>(
                                            new IRT::CLabelStatement(
                                                    labelJoin
                                            )
                                    )) )
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
                        std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CLabelStatement( labelTrue ))),
                        std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CSeqStatement(
                                std::move( wrapperTargetPositive->ToStatement()),
                                std::move( suffix )
                        )))
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

    std::cout << "IRT builder: CWhileStm\n";
    statement.conditionExpression->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperCondition = std::move( wrapper );
    statement.statement->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> wrapperBody = std::move( wrapper );

    IRT::CLabel labelLoop;
    IRT::CLabel labelBody;
    IRT::CLabel labelDone;

    std::unique_ptr<const IRT::CStatement> suffix(
            std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CSeqStatement(
                    std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CJumpStatement(
                            std::move(
                                    std::unique_ptr<const IRT::CLabelStatement>(
                                            new IRT::CLabelStatement(
                                                    labelLoop
                                            )
                                    )
                            )))),
                    std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CLabelStatement( labelDone )))
            )))
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
            std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CSeqStatement(
                    std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CLabelStatement( labelLoop ))),
                    std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CSeqStatement(
                            std::move( wrapperCondition->ToConditional( labelBody, labelDone )),
                            std::move( std::unique_ptr<const IRT::CStatement>(
                                    new IRT::CSeqStatement(
                                            std::move( std::unique_ptr<const IRT::CStatement>(
                                                    new IRT::CLabelStatement( labelBody )
                                            )),
                                            std::move( suffix )
                                    )
                            ))
                    )))
            )))
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

    std::cout << "IRT builder: CMethodStm\n";
    currentMethod = statement.name->name;
    buildNewFrame( &statement );
    std::string methodFullName = GetMethodFullName( currentFrame->GetClassName(), currentFrame->GetMethodName());

    statement.statements->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> statementListWrapper = std::move( wrapper );

    statement.returnExp->Accept( *this );
    std::unique_ptr<const IRT::CExpression> expressionReturn = std::move( wrapper->ToExpression());

    if( statementListWrapper ) {
        updateSubtreeWrapper( new IRT::CStatementWrapper(
                std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CSeqStatement(
                        std::move( std::unique_ptr<const IRT::CStatement>(
                                new IRT::CLabelStatement( IRT::CLabel( methodFullName )))),
                        std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CSeqStatement(
                                std::move( statementListWrapper->ToStatement()),
                                std::move( std::unique_ptr<const IRT::CStatement>(
                                        new IRT::CMoveStatement(
                                                std::move( currentFrame->GetReturnValueAddress()->ToExpression()),
                                                std::move( expressionReturn )
                                        )
                                ))
                        )))
                )))
        ));
    } else {
        updateSubtreeWrapper( new IRT::CStatementWrapper(
                std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CSeqStatement(
                        std::move( std::unique_ptr<const IRT::CStatement>(
                                new IRT::CLabelStatement( IRT::CLabel( methodFullName )))),
                        std::move( std::unique_ptr<const IRT::CStatement>( new IRT::CMoveStatement(
                                std::move( currentFrame->GetReturnValueAddress()->ToExpression()),
                                std::move( expressionReturn )
                        )))
                )))
        ));
    }

    treesOfMethods->emplace( methodFullName, std::move( wrapper->ToStatement()));
}

void CBuildVisitor::Visit( CMethodList &stm ) {
//    Should never be called
    assert( false );
}

void CBuildVisitor::Visit( CClass &statement ) {
    std::cout << "IRT builder: CClass\n";
    currentClassName = statement.id->name;
    std::vector<std::unique_ptr<CMethod>> &methodDeclarations = statement.methods->methods;
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
    std::cout << "IRT builder: CMainClass\n";
    currentMethod = MAIN_NAME;
    currentClassName = statement.id->name;
    buildNewFrame( &statement );
    std::string methodFullName = GetMethodFullName( currentFrame->GetClassName(), currentFrame->GetMethodName());

    statement.mainMethod->statements->Accept( *this );
    std::unique_ptr<IRT::ISubtreeWrapper> statementListWrapper = std::move( wrapper );
    if( statementListWrapper ) {
        updateSubtreeWrapper( new IRT::CStatementWrapper(
                new IRT::CSeqStatement(
                        std::move( std::unique_ptr<const IRT::CStatement>(
                                new IRT::CLabelStatement( IRT::CLabel( methodFullName ))
                        )),
                        std::move( statementListWrapper->ToStatement())
                )
        ));
    } else {
        // empty function
        updateSubtreeWrapper( new IRT::CStatementWrapper(
                new IRT::CLabelStatement( IRT::CLabel( methodFullName ))
        ));
    }

    treesOfMethods->emplace( methodFullName, std::move( wrapper->ToStatement()));
}

void CBuildVisitor::Visit( CProgram &statement ) {
    std::cout << "IRT builder: CProgram\n";
    statement.mainClass->Accept( *this );
    std::vector<std::unique_ptr<CClass>> &classDeclarations = statement.classList->classes;
    for( auto it = classDeclarations.begin(); it != classDeclarations.end(); ++it ) {
        (*it)->Accept( *this );
    }
}

std::shared_ptr<const MethodToIRTMap> CBuildVisitor::GetMethodFromIrtMap() {
    return treesOfMethods;
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

void CBuildVisitor::updateSubtreeWrapper( IRT::ISubtreeWrapper *_wrapper ) {
    wrapper = std::unique_ptr<IRT::ISubtreeWrapper>( _wrapper );
}

void CBuildVisitor::updateSubtreeWrapper( std::unique_ptr<IRT::ISubtreeWrapper> _wrapper ) {
    wrapper = std::move( _wrapper );
}

std::string CBuildVisitor::GetMethodFullName( const std::string &className, const std::string &methodName ) {
    return className + "::" + methodName;
}

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

void CBuildVisitor::buildNewFrame( const CMethod *declaration ) {
    std::shared_ptr<const ClassInfo> classDefinition = symbolTable->classes.at( currentClassName );
    std::shared_ptr<const MethodInfo> methodDefinition = classDefinition->methods.at( declaration->name->name );

    const std::vector<std::unique_ptr<CArgument>> &arguments = declaration->arguments->arguments;
    std::vector<std::string> argumentsNames;
    argumentsNames.reserve( arguments.size());
    for( auto it = arguments.begin(); it != arguments.end(); ++it ) {
        argumentsNames.push_back((*it)->id->name );
    }
    auto localNames = methodDefinition->fields->variableNames;

    auto fieldsNames = std::list<std::string>();
    std::shared_ptr<const ClassInfo> baseClass = classDefinition;
    while( baseClass ) {
        auto fields = baseClass->fields->variableNames;
        for( auto name : fields ) {
            fieldsNames.push_back( name );
        }
        baseClass = baseClass->baseClass != "" ? symbolTable->classes.at( baseClass->baseClass ) : nullptr;
    }

    buildNewFrame( currentClassName, declaration->name->name, argumentsNames.begin(), argumentsNames.end(),
                   localNames.begin(), localNames.end(), fieldsNames.begin(), fieldsNames.end());
}

void CBuildVisitor::buildNewFrame( const CMainClass *mainClass ) {
    std::list<std::string> emptySet;
    std::shared_ptr<const ClassInfo> classDefinition = symbolTable->classes.at( currentClassName );
    std::shared_ptr<const MethodInfo> methodDefinition = classDefinition->methods.at( MAIN_NAME );
    auto localNames = methodDefinition->fields->variableNames;

    buildNewFrame( mainClass->id->name, "main", emptySet.end(), emptySet.end(),
                   localNames.begin(), localNames.end(), emptySet.end(), emptySet.end());
}

void CBuildVisitor::Visit(CThisExpression &exp) {
    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move( currentFrame->GetThisAddress()->ToExpression() )
    ) );

    currentObjectClassName = currentClassName;
}

void CBuildVisitor::Visit(CGetFieldByThisExpression &exp) {
    std::cout << "IRT builder: CGetFieldByThisExpression\n";
    updateSubtreeWrapper( new IRT::CExpressionWrapper(
            std::move(currentFrame->GetClassFieldAddress(exp.fieldIdentifier->name)->ToExpression())));

    auto varInfo = getVariableInfoFromLocalArgAndFields(symbolTable,
                                                        currentClassName,
                                                        "",
                                                        exp.fieldIdentifier->name);

    if (varInfo->type->isPrimitive) {
        currentObjectClassName = "";
    } else {
        currentObjectClassName = varInfo->type->className;
    }
}

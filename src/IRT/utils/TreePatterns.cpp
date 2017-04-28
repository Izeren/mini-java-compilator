//
// Created by izeren on 4/25/17.
//

#include <cassert>
#include "TreePatterns.h"
#include "../nodes/Expressions.h"
#include "../nodes/Statements.h"


using ConstExpressionPtr = const IRT::CExpression *;
using ConstStatementPtr = const IRT::CStatement *;
using ConstBinopPtr = const IRT::CBinopExpression *;
using ConstTempPtr = const IRT::CTempExpression *;
using ConstConstPtr = const IRT::CConstExpression *;
using ConstMemPtr = const IRT::CMemExpression *;
using ConstLabelPtr = const IRT::CLabelStatement *;
using ConstNamePtr = const IRT::CNameExpression *;
using ConstCallPtr = const IRT::CCallExpression *;
using ConstExpStmPtr = const IRT::CExpStatement *;
using ConstMovePtr = const IRT::CMoveStatement *;
using ConstJumpPtr = const IRT::CJumpStatement *;
using ConstCJumpPtr = const IRT::CJumpConditionalStatement *;


std::shared_ptr<IRT::INode> IRT::TreePattern::GetPatternRepresentation( ) {
    return treeRepresentation;
}

std::string IRT::TreePattern::GetStringRepresentation( ) {
    return stringRepresentation;
}

IRT::TreePattern::~TreePattern( ) {
}

IRT::TreePattern::TreePattern( ) : treeRepresentation( NULL ), stringRepresentation( "" ) { }


IRT::RegPlusRegPattern::RegPlusRegPattern( ) {

}

bool
IRT::RegPlusRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                           AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::PLUS ) {
        ConstTempPtr leftRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getLeftOperand( ));
        if ( leftRegisterPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegisterPtr->getTemprorary( )));
        } else {
            CTemp leftRegister;
            children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
            commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
        }
        ConstTempPtr rightRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getRightOperand( ));
        if ( rightRegisterPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::AddRegRegCommand>( dest, rightRegisterPtr->getTemprorary( )));
        } else {
            CTemp rightRegister;
            children.push_back( std::make_pair( rightRegister, binopPtr->getRightOperand( )));
            commands.emplace_back( std::make_shared<AssemblyCode::AddRegRegCommand>( dest, rightRegister ));
        }
        return true;
    }
    return false;
}

IRT::RegMinusRegPattern::RegMinusRegPattern( ) { }

bool IRT::RegMinusRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest,
                                                 ChildrenTemps &children, AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::MINUS ) {
        ConstTempPtr leftRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getLeftOperand( ));
        if ( leftRegisterPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegisterPtr->getTemprorary( )));
        } else {
            CTemp leftRegister;
            children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
            commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
        }
        ConstTempPtr rightRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getRightOperand( ));
        if ( rightRegisterPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::SubRegRegCommand>( dest, rightRegisterPtr->getTemprorary( )));
        } else {
            CTemp rightRegister;
            children.push_back( std::make_pair( rightRegister, binopPtr->getRightOperand( )));
            commands.emplace_back( std::make_shared<AssemblyCode::SubRegRegCommand>( dest, rightRegister ));
        }
        return true;
    }
    return false;
}


IRT::RegMulRegPattern::RegMulRegPattern( ) { }

bool IRT::RegMulRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                               AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::MULTYPLY ) {
        ConstTempPtr leftRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getLeftOperand( ));
        if ( leftRegisterPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegisterPtr->getTemprorary( )));
        } else {
            CTemp leftRegister;
            children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
            commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
        }
        ConstTempPtr rightRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getRightOperand( ));
        if ( rightRegisterPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::MulRegRegCommand>( dest, rightRegisterPtr->getTemprorary( )));
        } else {
            CTemp rightRegister;
            children.push_back( std::make_pair( rightRegister, binopPtr->getRightOperand( )));
            commands.emplace_back( std::make_shared<AssemblyCode::MulRegRegCommand>( dest, rightRegister ));
        }
        return true;
    }
    return false;
}

IRT::RegModRegPattern::RegModRegPattern( ) { }

bool IRT::RegModRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                               AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::MOD ) {
        ConstTempPtr leftRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getLeftOperand( ));
        if ( leftRegisterPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegisterPtr->getTemprorary( )));
        } else {
            CTemp leftRegister;
            children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
            commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
        }
        ConstTempPtr rightRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getRightOperand( ));
        if ( rightRegisterPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::DivRegRegCommand>( dest, rightRegisterPtr->getTemprorary( )));
        } else {
            CTemp rightRegister;
            children.push_back( std::make_pair( rightRegister, binopPtr->getRightOperand( )));
            commands.emplace_back( std::make_shared<AssemblyCode::DivRegRegCommand>( dest, rightRegister ));
        }
        return true;
    }
    return false;
}

bool IRT::ConstPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                           AssemblyCommands &commands ) {
    ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(tree);
    if ( constPtr ) {
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegConstCommand>( dest, constPtr->getValue( )));
        return true;
    }
    return false;
}

bool IRT::MemPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                         AssemblyCommands &commands ) {
    ConstMemPtr memPtr = dynamic_cast<ConstMemPtr>(tree);
    if ( memPtr ) {
        ConstTempPtr constTempPtr = dynamic_cast<ConstTempPtr>(memPtr->getAddress( ));
        if ( constTempPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::MoveRegMemCommand>( dest, constTempPtr->getTemprorary( )));
        } else {
            CTemp source;
            children.push_back( std::make_pair( source, memPtr->getAddress( )));
            commands.emplace_back( std::make_shared<AssemblyCode::MoveRegMemCommand>( dest, source ));
        }
        return true;
    }
    return false;
}

bool IRT::RegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                         AssemblyCommands &commands ) {
    assert( false );
}

bool IRT::LabelPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                           AssemblyCommands &commands ) {
    ConstLabelPtr labelPtr = dynamic_cast<ConstLabelPtr>(tree);
    if ( labelPtr ) {
        commands.emplace_back( std::make_shared<AssemblyCode::LabelCommand>( labelPtr->Label( ).ToString( )));
        return true;
    }
    return false;
}

bool IRT::NamePattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                          AssemblyCommands &commands ) {
    ConstNamePtr namePtr = dynamic_cast<ConstNamePtr>(tree);
    if ( namePtr ) {
        commands.emplace_back( std::make_shared<AssemblyCode::NameCommand>( dest, namePtr->getLabel( ).ToString( )));
        return true;
    }
    return false;
}

bool IRT::ExpPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                         AssemblyCommands &commands ) {
    ConstExpStmPtr expStmPtr = dynamic_cast<ConstExpStmPtr>(tree);
    if ( expStmPtr ) {
        ConstTempPtr registerPtr = dynamic_cast<ConstTempPtr>(expStmPtr->Expression( ));
        if ( registerPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, registerPtr->getTemprorary( )));
        } else {
            CTemp source;
            children.push_back( std::make_pair( source, expStmPtr->Expression( )));
            commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, source ));
        }
        return true;
    }
    return false;
}

bool IRT::CallPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                          AssemblyCommands &commands ) {
    ConstCallPtr callPtr = dynamic_cast<ConstCallPtr>(tree);
    if ( callPtr ) {
        const std::vector<std::unique_ptr<const CExpression>> &argumentsPtr = callPtr->getArguments( )->getExpressions( );
        std::vector<CTemp> arguments;
        CTemp address;
        children.push_back( std::make_pair( address, callPtr->getFunction( )));
        for ( int index = 0; index < argumentsPtr.size( ); ++index ) {
            CTemp child;
            children.push_back( std::make_pair( child, argumentsPtr[ index ].get( )));
            arguments.push_back( child );
        }
        commands.emplace_back( std::make_shared<AssemblyCode::CallCommand>( address, arguments ));
        return true;
    }
    return false;
}

bool IRT::MoveRegRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                                AssemblyCommands &commands ) {
    assert( false );  //pretended not to be ever used as a pattern rather than simple command
    ConstMovePtr movePtr = dynamic_cast<ConstMovePtr>(tree);
    if ( movePtr ) {
        CTemp leftRegister;
        CTemp rightRegister;
        children.push_back( std::make_pair( leftRegister, movePtr->Target( )));
        children.push_back( std::make_pair( rightRegister, movePtr->Source( )));
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( leftRegister, rightRegister ));
        return true;
    }
    return false;
}

bool IRT::JumpPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                          AssemblyCommands &commands ) {
    ConstJumpPtr jumpPtr = dynamic_cast<ConstJumpPtr>(tree);
    if ( jumpPtr ) {
        commands.emplace_back(
                std::make_shared<AssemblyCode::JumpCommand>( jumpPtr->getLabel( )->Label( ).ToString( )));
        return true;
    }
    return false;
}


bool
IRT::ConditionalJumpPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                                AssemblyCommands &commands ) {
    ConstCJumpPtr cJumpPtr = dynamic_cast<ConstCJumpPtr>(tree);
    if ( cJumpPtr ) {
        CTemp leftOperand;
        CTemp rightOperand;
        children.push_back( std::make_pair( leftOperand, cJumpPtr->LeftOperand( )));
        children.push_back( std::make_pair( rightOperand, cJumpPtr->RightOperand( )));
        switch ( cJumpPtr->Operation( )) {
            case IRT::enums::TLogicOperator::LESS : {
                commands.emplace_back( std::make_shared<AssemblyCode::CJumpLessCommand>( leftOperand, rightOperand,
                                                                                         cJumpPtr->TrueLabel( )->Label( ).ToString( )));
                break;
            }
            case IRT::enums::TLogicOperator::GREATER : {
                commands.emplace_back( std::make_shared<AssemblyCode::CJumpLessCommand>( rightOperand, leftOperand,
                                                                                         cJumpPtr->TrueLabel( )->Label( ).ToString( )));
                break;
            }
            case IRT::enums::TLogicOperator::EQUALS : {
                commands.emplace_back( std::make_shared<AssemblyCode::CJumpEqualCommand>( leftOperand, rightOperand,
                                                                                          cJumpPtr->TrueLabel( )->Label( ).ToString( )));
                break;
            }
            case IRT::enums::TLogicOperator::NOT_EQUALS : {
                commands.emplace_back( std::make_shared<AssemblyCode::CJumpNotEqualCommand>( leftOperand, rightOperand,
                                                                                             cJumpPtr->TrueLabel( )->Label( ).ToString( )));
                break;
            }
            default: {
                assert( false );
            }
        }
        return true;
    }
    return false;
}

bool
IRT::RegPlusConstPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                             AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::PLUS ) {
        ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(binopPtr->getRightOperand( ));
        if ( constPtr ) {
            ConstTempPtr leftRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getLeftOperand( ));
            if ( leftRegisterPtr ) {
                commands.emplace_back(
                        std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegisterPtr->getTemprorary( )));
            } else {
                CTemp leftRegister;
                children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
                commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
            }
            commands.emplace_back( std::make_shared<AssemblyCode::AddRegConstCommand>( dest, constPtr->getValue( )));
            return true;
        }
    }
    return false;
}

bool
IRT::ConstPlusRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                             AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::PLUS ) {
        ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(binopPtr->getLeftOperand( ));
        if ( constPtr ) {
            ConstTempPtr rightRegisterPtr = dynamic_cast<ConstTempPtr>(binopPtr->getRightOperand( ));
            if ( rightRegisterPtr ) {
                commands.emplace_back(
                        std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, rightRegisterPtr->getTemprorary( )));
            } else {
                CTemp rightRegister;
                children.push_back( std::make_pair( rightRegister, binopPtr->getLeftOperand( )));
                commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, rightRegister ));
            }
            commands.emplace_back( std::make_shared<AssemblyCode::AddRegConstCommand>( dest, constPtr->getValue( )));
            return true;
        }
    }
    return false;
}

bool IRT::MemFromRegPlusConstPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest,
                                                         ChildrenTemps &children, AssemblyCommands &commands ) {
    ConstMemPtr memPtr = dynamic_cast<ConstMemPtr>(tree);
    if ( memPtr ) {
        ConstBinopPtr constBinopPtr = dynamic_cast<ConstBinopPtr>(memPtr->getAddress( ));
        if ( constBinopPtr ) {
            ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(constBinopPtr->getRightOperand( ));
            if ( constPtr ) {
                ConstTempPtr constTempPtr = dynamic_cast<ConstTempPtr>(constBinopPtr->getLeftOperand( ));
                if ( constTempPtr ) {
                    commands.emplace_back(
                            std::make_shared<AssemblyCode::MoveMemFromRegPlusConstToReg>( dest,
                                                                                          constTempPtr->getTemprorary( ),
                                                                                          constPtr->getValue( )));
                } else {
                    CTemp source;
                    children.push_back( std::make_pair( source, memPtr->getAddress( )));
                    commands.emplace_back(
                            std::make_shared<AssemblyCode::MoveMemFromRegPlusConstToReg>( dest, source,
                                                                                          constPtr->getValue( )));
                }
                return true;
            }
        }
    }
    return false;
}

bool IRT::MemFromConstPlusRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest,
                                                         ChildrenTemps &children, AssemblyCommands &commands ) {
    ConstMemPtr memPtr = dynamic_cast<ConstMemPtr>(tree);
    if ( memPtr ) {
        ConstBinopPtr constBinopPtr = dynamic_cast<ConstBinopPtr>(memPtr->getAddress( ));
        if ( constBinopPtr ) {
            ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(constBinopPtr->getLeftOperand( ));
            if ( constPtr ) {
                ConstTempPtr constTempPtr = dynamic_cast<ConstTempPtr>(constBinopPtr->getRightOperand( ));
                if ( constTempPtr ) {
                    commands.emplace_back(
                            std::make_shared<AssemblyCode::MoveMemFromRegPlusConstToReg>( dest,
                                                                                          constTempPtr->getTemprorary( ),
                                                                                          constPtr->getValue( )));
                } else {
                    CTemp source;
                    children.push_back( std::make_pair( source, memPtr->getAddress( )));
                    commands.emplace_back(
                            std::make_shared<AssemblyCode::MoveMemFromRegPlusConstToReg>( dest, source,
                                                                                          constPtr->getValue( )));
                }
                return true;
            }
        }
    }
    return false;
}

bool
IRT::MemFromConstPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                             AssemblyCommands &commands ) {
    ConstMemPtr memPtr = dynamic_cast<ConstMemPtr>(tree);
    if ( memPtr ) {
        ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(memPtr->getAddress( ));
        if ( constPtr ) {
            commands.emplace_back(
                    std::make_shared<AssemblyCode::MoveMemFromConstCommand>( dest, constPtr->getValue( )));
            return true;
        }
    }
    return false;
}

bool IRT::MoveRegToMemByRegPlusConst::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest,
                                                         ChildrenTemps &children, AssemblyCommands &commands ) {
    ConstMovePtr movePtr = dynamic_cast<ConstMovePtr>(tree);
    if ( movePtr ) {
        ConstMemPtr memPtr = dynamic_cast<ConstMemPtr>(movePtr->Target( ));
        if ( memPtr ) {
            ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(memPtr->getAddress( ));
            if ( binopPtr ) {
                ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(binopPtr->getRightOperand( ));
                if ( constPtr ) {
                    ConstTempPtr targetRegPtr = dynamic_cast<ConstTempPtr>(binopPtr->getLeftOperand( ));
                    ConstTempPtr sourceRegPtr = dynamic_cast<ConstTempPtr>(movePtr->Source( ));
                    CTemp leftRegister;
                    CTemp rightRegister;
                    if ( !targetRegPtr ) {
                        children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand()));
                    } else {
                        leftRegister = targetRegPtr->getTemprorary( );
                    }
                    if ( !sourceRegPtr ) {
                        children.push_back( std::make_pair( rightRegister, movePtr->Source()));
                    } else {
                        rightRegister = sourceRegPtr->getTemprorary( );
                    }
                    commands.emplace_back( std::make_shared<AssemblyCode::MoveRegToMemByRegPlusConst>( leftRegister,
                                                                                                       constPtr->getValue( ),
                                                                                                       rightRegister ));
                    return true;
                }
            }
        }
    }
    return false;
}

bool IRT::MoveRegToMemByConstPlusReg::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest,
                                                         ChildrenTemps &children, AssemblyCommands &commands ) {
    ConstMovePtr movePtr = dynamic_cast<ConstMovePtr>(tree);
    if ( movePtr ) {
        ConstMemPtr memPtr = dynamic_cast<ConstMemPtr>(movePtr->Target( ));
        if ( memPtr ) {
            ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(memPtr->getAddress( ));
            if ( binopPtr ) {
                ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(binopPtr->getLeftOperand( ));
                if ( constPtr ) {
                    ConstTempPtr targetRegPtr = dynamic_cast<ConstTempPtr>(binopPtr->getRightOperand( ));
                    ConstTempPtr sourceRegPtr = dynamic_cast<ConstTempPtr>(movePtr->Source( ));
                    CTemp leftRegister;
                    CTemp rightRegister;
                    if ( !targetRegPtr ) {
                        children.push_back( std::make_pair( leftRegister, binopPtr->getRightOperand()));
                    } else {
                        leftRegister = targetRegPtr->getTemprorary( );
                    }
                    if ( !sourceRegPtr ) {
                        children.push_back( std::make_pair( rightRegister, movePtr->Source()));
                    } else {
                        rightRegister = sourceRegPtr->getTemprorary( );
                    }
                    commands.emplace_back( std::make_shared<AssemblyCode::MoveRegToMemByRegPlusConst>( leftRegister,
                                                                                                       constPtr->getValue( ),
                                                                                                       rightRegister ));
                    return true;
                }
            }
        }
    }
    return false;
}

bool
IRT::MoveRegToMemByConst::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                             AssemblyCommands &commands ) {
    ConstMovePtr movePtr = dynamic_cast<ConstMovePtr>(tree);
    if ( movePtr ) {
        ConstMemPtr memPtr = dynamic_cast<ConstMemPtr>(movePtr->Target( ));
        if ( memPtr ) {
            ConstConstPtr constPtr = dynamic_cast<ConstConstPtr>(memPtr->getAddress( ));
            if ( constPtr ) {
                ConstTempPtr sourceRegPtr = dynamic_cast<ConstTempPtr>(movePtr->Source( ));
                CTemp rightRegister;
                if ( !sourceRegPtr ) {
                    children.push_back( std::make_pair( rightRegister, movePtr->Source()));
                } else {
                    rightRegister = sourceRegPtr->getTemprorary( );
                }
                commands.emplace_back( std::make_shared<AssemblyCode::MoveRegToMemByConst>(
                        constPtr->getValue( ),
                        rightRegister ));
                return true;
            }
        }
    }
    return false;
}

bool IRT::MoveRegToMemByReg::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                                AssemblyCommands &commands ) {
    ConstMovePtr movePtr = dynamic_cast<ConstMovePtr>(tree);
    if ( movePtr ) {
        ConstMemPtr memPtr = dynamic_cast<ConstMemPtr>(movePtr->Target( ));
        if ( memPtr ) {
            ConstTempPtr targetRegPtr = dynamic_cast<ConstTempPtr>(memPtr->getAddress( ));
            ConstTempPtr sourceRegPtr = dynamic_cast<ConstTempPtr>(movePtr->Source( ));
            CTemp leftRegister;
            CTemp rightRegister;
            if ( !targetRegPtr ) {
                children.push_back( std::make_pair( leftRegister, memPtr->getAddress()));
            } else {
                leftRegister = targetRegPtr->getTemprorary( );
            }
            if ( !sourceRegPtr ) {
                children.push_back( std::make_pair( rightRegister, movePtr->Source()));
            } else {
                rightRegister = sourceRegPtr->getTemprorary( );
            }
            commands.emplace_back( std::make_shared<AssemblyCode::MoveRegToMemByReg>( leftRegister,
                                                                                      rightRegister ));
            return true;
        }
    }
    return false;
}

bool IRT::MoveFromMemByRegToMemByReg::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest,
                                                         ChildrenTemps &children, AssemblyCommands &commands ) {
    ConstMovePtr movePtr = dynamic_cast<ConstMovePtr>(tree);
    if ( movePtr ) {
        ConstMemPtr leftMemPtr = dynamic_cast<ConstMemPtr>(movePtr->Target( ));
        ConstMemPtr rightMemPtr = dynamic_cast<ConstMemPtr>(movePtr->Source( ));
        if ( leftMemPtr && rightMemPtr ) {
            ConstTempPtr targetRegPtr = dynamic_cast<ConstTempPtr>(leftMemPtr->getAddress( ));
            ConstTempPtr sourceRegPtr = dynamic_cast<ConstTempPtr>(rightMemPtr->getAddress());
            CTemp leftRegister;
            CTemp rightRegister;
            if ( !targetRegPtr ) {
                children.push_back( std::make_pair( leftRegister, leftMemPtr->getAddress()));
            } else {
                leftRegister = targetRegPtr->getTemprorary( );
            }
            if ( !sourceRegPtr ) {
                children.push_back( std::make_pair( rightRegister, rightMemPtr->getAddress()));
            } else {
                rightRegister = sourceRegPtr->getTemprorary( );
            }
            commands.emplace_back( std::make_shared<AssemblyCode::MoveRegFromMemToMemByReg>( leftRegister,
                                                                                      rightRegister ));
            return true;
        }
    }
    return false;
}

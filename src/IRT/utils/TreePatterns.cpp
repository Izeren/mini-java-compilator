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
        CTemp leftRegister;
        CTemp rightRegister;
        children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
        children.push_back( std::make_pair( rightRegister, binopPtr->getRightOperand( )));
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
        commands.emplace_back( std::make_shared<AssemblyCode::AddRegRegCommand>( dest, rightRegister ));
        return true;
    }
    return false;
}

IRT::RegMinusRegPattern::RegMinusRegPattern( ) { }

bool IRT::RegMinusRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest,
                                                 ChildrenTemps &children, AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::MINUS ) {
        CTemp leftRegister;
        CTemp rightRegister;
        children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
        children.push_back( std::make_pair( rightRegister, binopPtr->getRightOperand( )));
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
        commands.emplace_back( std::make_shared<AssemblyCode::SubRegRegCommand>( dest, rightRegister ));
        return true;
    }
    return false;
}


IRT::RegMulRegPattern::RegMulRegPattern( ) { }

bool IRT::RegMulRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                               AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::MULTYPLY ) {
        CTemp leftRegister;
        CTemp rightRegister;
        children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
        children.push_back( std::make_pair( rightRegister, binopPtr->getRightOperand( )));
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
        commands.emplace_back( std::make_shared<AssemblyCode::MulRegRegCommand>( dest, rightRegister ));
        return true;
    }
    return false;
}

IRT::RegModRegPattern::RegModRegPattern( ) { }

bool IRT::RegModRegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                               AssemblyCommands &commands ) {
    ConstBinopPtr binopPtr = dynamic_cast<ConstBinopPtr>(tree);
    if ( binopPtr && binopPtr->getOperation( ) == IRT::enums::TOperationType::MOD ) {
        CTemp leftRegister;
        CTemp rightRegister;
        children.push_back( std::make_pair( leftRegister, binopPtr->getLeftOperand( )));
        children.push_back( std::make_pair( rightRegister, binopPtr->getRightOperand( )));
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, leftRegister ));
        commands.emplace_back( std::make_shared<AssemblyCode::DivRegRegCommand>( dest, rightRegister ));
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
        CTemp source;
        children.push_back( std::make_pair( source, memPtr->getAddress( )));
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegMemCommand>( dest, source ));
        return true;
    }
    return false;
}

bool IRT::RegPattern::TryToGenerateCode( const IRT::INode *tree, const IRT::CTemp &dest, ChildrenTemps &children,
                                         AssemblyCommands &commands ) {
    ConstTempPtr tempPtr = dynamic_cast<ConstTempPtr>(tree);
    if ( tempPtr ) {
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, tempPtr->getTemprorary( )));
        return true;
    }
    return false;
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
        CTemp source;
        children.push_back( std::make_pair( source, expStmPtr->Expression( )));
        commands.emplace_back( std::make_shared<AssemblyCode::MoveRegRegCommand>( dest, source ));
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

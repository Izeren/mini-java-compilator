//
// Created by izeren on 4/25/17.
//

#include "TreePatterns.h"
#include "../nodes/Expressions.h"
#include "../nodes/Statements.h"


typedef std::unique_ptr<const IRT::CExpression> ConstExpressionPtr;
using ConstStatementPtr = std::unique_ptr<const IRT::CStatement>;
using ConstBinopPtr = std::unique_ptr<const IRT::CBinopExpression>;
using ConstTempPtr = std::unique_ptr<const IRT::CTempExpression>;

#define MOVE_UNI_TEMP( value ) std::move(std::unique_ptr<CTempExpression>(value))
#define MOVE_UNI_BINOP( value ) std::move(std::unique_ptr<CBinopExpression>(value))
#define MOVE_UNI_MEM( value ) std::move(std::unique_ptr<CMemExpression>(value))
#define MOVE_UNI_CONST( value ) std::move(std::unique_ptr<CConstExpression>(value))
#define MOVE_UNI_MOVE( value ) std::move(std::unique_ptr<CMoveStatement>(value))


std::shared_ptr<IRT::INode> IRT::TreePattern::GetPatternRepresentation( ) {
    return treeRepresentation;
}

std::string IRT::TreePattern::GetStringRepresentation( ) {
    return stringRepresentation;
}

IRT::TreePattern::~TreePattern( ) {
}

IRT::TreePattern::TreePattern( ) : treeRepresentation( NULL ), stringRepresentation( "" ) { }


IRT::RegPlusRegToRegPattern::RegPlusRegToRegPattern( ) {
    CTemp leftReg;
    CTemp rightReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_TEMP( new CTempExpression( leftReg ));
    ConstExpressionPtr rightExpression = MOVE_UNI_TEMP( new CTempExpression( rightReg ));

    treeRepresentation = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::PLUS ));
}

IRT::RegMinusRegToRegPattern::RegMinusRegToRegPattern( ) {
    CTemp leftReg;
    CTemp rightReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_TEMP( new CTempExpression( leftReg ));
    ConstExpressionPtr rightExpression = MOVE_UNI_TEMP( new CTempExpression( rightReg ));

    treeRepresentation = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::MINUS ));
}

IRT::RegMulRegToRegPattern::RegMulRegToRegPattern( ) {
    CTemp leftReg;
    CTemp rightReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_TEMP( new CTempExpression( leftReg ));
    ConstExpressionPtr rightExpression = MOVE_UNI_TEMP( new CTempExpression( rightReg ));

    treeRepresentation = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::MULTYPLY ));
}

IRT::RegModRegToRegPattern::RegModRegToRegPattern( ) {
    CTemp leftReg;
    CTemp rightReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_TEMP( new CTempExpression( leftReg ));
    ConstExpressionPtr rightExpression = MOVE_UNI_TEMP( new CTempExpression( rightReg ));

    treeRepresentation = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::MOD ));
}

IRT::RegPlusConstToRegPattern::RegPlusConstToRegPattern( ) {
    CTemp leftReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_TEMP( new CTempExpression( leftReg ));
    ConstExpressionPtr rightExpression = MOVE_UNI_CONST( new CConstExpression( 0 ));

    treeRepresentation = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::PLUS ));
}

IRT::ConstPlusRegToRegPattern::ConstPlusRegToRegPattern( ) {
    CTemp rightReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_CONST( new CConstExpression( 0 ));
    ConstExpressionPtr rightExpression = MOVE_UNI_TEMP( new CTempExpression( rightReg ));

    treeRepresentation = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::PLUS ));
}

IRT::ConstToRegPattern::ConstToRegPattern( ) {
    treeRepresentation = MOVE_UNI_CONST( new CConstExpression( 0 ));
}


IRT::RegMinusConstToRegPattern::RegMinusConstToRegPattern( ) {
    CTemp leftReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_TEMP( new CTempExpression( leftReg ));
    ConstExpressionPtr rightExpression = MOVE_UNI_CONST( new CConstExpression( 0 ));

    treeRepresentation = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::MINUS ));
}


IRT::MemFromRegPlusConstToRegPattern::MemFromRegPlusConstToRegPattern( ) {
    CTemp leftReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_TEMP( new CTempExpression( leftReg ));
    ConstExpressionPtr rightExpression = MOVE_UNI_CONST( new CConstExpression( 0 ));

    ConstExpressionPtr binopExpression = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::PLUS ));
    treeRepresentation = MOVE_UNI_MEM( new CMemExpression( std::move( binopExpression )));
}


IRT::MemFromConstPlusRegToRegPattern::MemFromConstPlusRegToRegPattern( ) {
    CTemp rightReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_CONST( new CConstExpression( 0 ));
    ConstExpressionPtr rightExpression = MOVE_UNI_TEMP( new CTempExpression( rightReg ));

    ConstExpressionPtr binopExpression = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::PLUS ));
    treeRepresentation = MOVE_UNI_MEM( new CMemExpression( std::move( binopExpression )));
}


IRT::MemFromConstToRegPattern::MemFromConstToRegPattern( ) {
    ConstExpressionPtr expression = MOVE_UNI_CONST( new CConstExpression( 0 ));
    treeRepresentation = MOVE_UNI_MEM( new CMemExpression( std::move( expression )));
}

IRT::MemFromRegToRegPattern::MemFromRegToRegPattern( ) {
    CTemp temp;
    ConstExpressionPtr expression = MOVE_UNI_TEMP( new CTempExpression( temp ));
    treeRepresentation = MOVE_UNI_MEM( new CMemExpression( std::move( expression )));
}

IRT::MoveFromMemFromRegPlusConstToRegPattern::MoveFromMemFromRegPlusConstToRegPattern( ) {
    CTemp leftReg;
    CTemp resultReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_TEMP( new CTempExpression( leftReg ));
    ConstExpressionPtr rightExpression = MOVE_UNI_CONST( new CConstExpression( 0 ));
    ConstExpressionPtr resultExpression = MOVE_UNI_TEMP( new CTempExpression( resultReg ));
    ConstExpressionPtr binopExpression = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::PLUS ));
    ConstExpressionPtr memExpression = MOVE_UNI_MEM( new CMemExpression( std::move( binopExpression )));
    treeRepresentation = MOVE_UNI_MOVE(
            new CMoveStatement( std::move( resultExpression ), std::move( memExpression )));

}


IRT::MoveFromMemFromConstPlusRegToRegPattern::MoveFromMemFromConstPlusRegToRegPattern( ) {
    CTemp rightReg;
    CTemp resultReg;
    ConstExpressionPtr leftExpression = MOVE_UNI_CONST( new CConstExpression( 0 ));
    ConstExpressionPtr rightExpression = MOVE_UNI_TEMP( new CTempExpression( rightReg ));
    ConstExpressionPtr resultExpression = MOVE_UNI_TEMP( new CTempExpression( resultReg ));
    ConstExpressionPtr binopExpression = MOVE_UNI_BINOP(
            new CBinopExpression( std::move( leftExpression ), std::move( rightExpression ),
                                  IRT::enums::TOperationType::PLUS ));
    ConstExpressionPtr memExpression = MOVE_UNI_MEM( new CMemExpression( std::move( binopExpression )));
    treeRepresentation = MOVE_UNI_MOVE(
            new CMoveStatement( std::move( resultExpression ), std::move( memExpression )));
}


IRT::MoveFromMemFromConstToRegPattern::MoveFromMemFromConstToRegPattern( ) {
    CTemp resultReg;
    ConstExpressionPtr constExpression = MOVE_UNI_CONST( new CConstExpression( 0 ));
    ConstExpressionPtr resultExpression = MOVE_UNI_TEMP( new CTempExpression( resultReg ));
    ConstExpressionPtr memExpression = MOVE_UNI_MEM( new CMemExpression( std::move( constExpression )));
    treeRepresentation = MOVE_UNI_MOVE(
            new CMoveStatement( std::move( resultExpression ), std::move( memExpression )));
}


IRT::MoveFromMemFromRegToRegPattern::MoveFromMemFromRegToRegPattern( ) {
    CTemp reg;
    CTemp resultReg;
    ConstExpressionPtr regExpression = MOVE_UNI_TEMP( new CTempExpression( reg ));
    ConstExpressionPtr resultExpression = MOVE_UNI_TEMP( new CTempExpression( resultReg ));
    ConstExpressionPtr memExpression = MOVE_UNI_MEM( new CMemExpression( std::move( regExpression )));
    treeRepresentation = MOVE_UNI_MOVE(
            new CMoveStatement( std::move( resultExpression ), std::move( memExpression )));
}

IRT::MoveFromMemFromRegToMemToRegPattern::MoveFromMemFromRegToMemToRegPattern( ) {
    CTemp sourceReg;
    CTemp targetReg;
    ConstExpressionPtr sourceExpression = MOVE_UNI_TEMP( new CTempExpression( sourceReg ));
    ConstExpressionPtr targetExpression = MOVE_UNI_TEMP( new CTempExpression( targetReg ));
    ConstExpressionPtr sourceMemExpression = MOVE_UNI_MEM(
            new CMemExpression( std::move( sourceExpression )));
    ConstExpressionPtr targetMemExpression = MOVE_UNI_MEM(
            new CMemExpression( std::move( targetExpression )));
    treeRepresentation = MOVE_UNI_MOVE(
            new CMoveStatement( std::move( sourceExpression ), std::move( targetExpression )));

}


#undef MOVE_UNI_TEMP
#undef MOVE_UNI_BINOP
#undef MOVE_UNI_CONST
#undef MOVE_UNI_MEM
#undef MOVE_UNI_MOVE


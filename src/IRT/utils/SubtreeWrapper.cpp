//
// Created by izeren on 2/27/17.
//
#include "SubtreeWrapper.h"

namespace IRT {

    std::unique_ptr<const CExpression> CExpressionWrapper::ToExpression() {
        return std::move( expression );
    }

    std::unique_ptr<const CStatement> CExpressionWrapper::ToStatement() {
        return std::move( std::unique_ptr<const CStatement>( new CExpStatement( std::move( expression ))));
    }

    std::unique_ptr<const CStatement> CExpressionWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
        return std::move( std::unique_ptr<const CStatement>(
                new CJumpConditionalStatement(
                        enums::TLogicOperator::NOT_EQUALS,
                        std::move( expression ),
                        std::move( std::unique_ptr<const CExpression>( new CConstExpression( 0 ))),
                        std::move( std::unique_ptr<const CLabelStatement>( new CLabelStatement( labelTrue ))),
                        std::move( std::unique_ptr<const CLabelStatement>( new CLabelStatement( labelFalse )))
                )
        ));
    }


    std::unique_ptr<const CExpression> CStatementWrapper::ToExpression() {
        // Dummy realization;
        assert( false );
    }

    std::unique_ptr<const CStatement> CStatementWrapper::ToStatement() {
        return std::move( statement );
    }

    std::unique_ptr<const CStatement> CStatementWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
        // Dummy realization
        assert( false );
    }


    std::unique_ptr<const CExpression> CConditionalWrapper::ToExpression() {
        auto tempRegister = CTemp();
        std::unique_ptr<const CExpression> tempPtr_1 = std::unique_ptr<const CTempExpression>(
                new CTempExpression( tempRegister ));
        std::unique_ptr<const CExpression> tempPtr_0 = std::unique_ptr<const CTempExpression>(
                new CTempExpression( tempRegister ));
        std::unique_ptr<const CExpression> tempPtr_r = std::unique_ptr<const CTempExpression>(
                new CTempExpression( tempRegister ));
        std::unique_ptr<const CExpression> constPtr_0 = std::unique_ptr<const CConstExpression>(
                new CConstExpression( 0 ));
        std::unique_ptr<const CExpression> constPtr_1 = std::unique_ptr<const CConstExpression>(
                new CConstExpression( 1 ));

        CLabel labelFalse;
        CLabel labelTrue;
        return std::move( std::unique_ptr<const CExpression>(
                new CEseqExpression(
                        std::move( std::unique_ptr<const CStatement>( new CSeqStatement(
                                std::move( std::unique_ptr<const CStatement>(
                                        new CMoveStatement( std::move( tempPtr_1 ), std::move( constPtr_1 )))),
                                std::move( std::unique_ptr<const CStatement>( new CSeqStatement(
                                        std::move( ToConditional( labelTrue, labelFalse )),
                                        std::move( std::unique_ptr<const CStatement>(
                                                new CSeqStatement(
                                                        std::move( std::unique_ptr<const CStatement>(
                                                                new CLabelStatement( labelFalse ))),
                                                        std::move( std::unique_ptr<const CStatement>( new CSeqStatement(
                                                                std::move( std::unique_ptr<const CStatement>(
                                                                        new CMoveStatement( std::move( tempPtr_0 ),
                                                                                            std::move( constPtr_0 )))),
                                                                std::move( std::unique_ptr<const CStatement>(
                                                                        new CLabelStatement( labelTrue )))
                                                        )))
                                                )
                                        ))
                                )))
                        ))),
                        std::move( tempPtr_r )
                )
        ));
    }

    std::unique_ptr<const CStatement> CConditionalWrapper::ToStatement() {
        /* will be done later */
    }

    std::unique_ptr<const CStatement>
    CRelativeConditionalWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
        return std::move( std::unique_ptr<const CStatement>(
                new CJumpConditionalStatement(
                        operatorType,
                        std::move( operandLeft ),
                        std::move( operandRight ),
                        std::move( std::unique_ptr<const CLabelStatement>( new CLabelStatement( labelTrue ))),
                        std::move( std::unique_ptr<const CLabelStatement>( new CLabelStatement( labelFalse )))
                )
        ));
    }

    std::unique_ptr<const CStatement> CAndConditionalWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
        CLabel labelMiddle;
        return std::move( std::unique_ptr<const CStatement>(
                new CSeqStatement(
                        std::move( operandLeft->ToConditional( labelMiddle, labelFalse )),
                        std::move( std::unique_ptr<const CStatement>(
                                new CSeqStatement(
                                        std::move( std::unique_ptr<const CStatement>(
                                                new CLabelStatement( labelMiddle ))),
                                        std::move( operandRight->ToConditional( labelTrue, labelFalse ))
                                )
                        ))
                )
        ));
    }

    std::unique_ptr<const CStatement> COrConditionalWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
        CLabel labelMiddle;
        CLabelStatement *pointer = new CLabelStatement( labelMiddle );
        std::unique_ptr<const CStatement> ptr = std::unique_ptr<const CLabelStatement>( pointer );
        return std::move( std::unique_ptr<const CStatement>(
                new CSeqStatement(
                        std::move( operandLeft->ToConditional( labelTrue, labelMiddle )),
                        std::move( std::unique_ptr<const CStatement>(
                                new CSeqStatement(
                                        std::move( ptr ),
                                        std::move( operandRight->ToConditional( labelTrue, labelFalse ))
                                )
                        ))
                )
        ));
    }

    std::unique_ptr<const CStatement> CNegateConditionalWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
        return std::move( wrapper->ToConditional( labelFalse, labelTrue )); // need to swap true and false labels
    }
};

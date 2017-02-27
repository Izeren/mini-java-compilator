//
// Created by izeren on 2/19/17.
//
#pragma  once

namespace IRT {
    namespace enums {
        enum class TOperationType : char {
            PLUS,
            MINUS,
            MULTYPLY,
            MOD,
            AND,
            OR
        };

        enum class TLogicOperator : char {
            EQUALS,
            NOT_EQUALS,
            LESS,
            GREATER,
            LESS_OR_EQUAL,
            GREATER_OR_EQUAL,
            ULT, // ???
            ULE, // ???
            UGT, // ???
            UGE // ???
        };
    }
}

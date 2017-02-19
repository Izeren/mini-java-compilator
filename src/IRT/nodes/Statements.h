#pragma once

#include "INode.h"

namespace IRT {

class CStatement : public INode {
    // inherited
};

enum class TLogicOperator : char {
    EQUALS,
    NOT_EQUALS,
    LESS,
    GREATER,
    LESS_EQUAL,
    GREATER_EQUAL,

};

}
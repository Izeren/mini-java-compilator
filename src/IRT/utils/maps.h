#include <map>
#include <string>

namespace IRT {
    namespace maps {
        const std::map<IRT::enums::TOperationType, std::string> operationTypeToString = {
                { IRT::enums::TOperationType::PLUS, "PLUS"},
                { IRT::enums::TOperationType::MULTYPLY, "MULTIPLY"},
                { IRT::enums::TOperationType::OR, "OR"},
                { IRT::enums::TOperationType::AND, "AND"},
                { IRT::enums::TOperationType::MOD, "MOD"}
        };

        const std::map<IRT::enums::TLogicOperator, std::string> logicOperationToString = {
                { IRT::enums::TLogicOperator::EQUALS, "EQUALS"},
                { IRT::enums::TLogicOperator::GREATER, "GREATER"},
                { IRT::enums::TLogicOperator::LESS, "LESS"},
                { IRT::enums::TLogicOperator::GREATER_OR_EQUAL, "GREATER_OR_EQUAL"},
                { IRT::enums::TLogicOperator::LESS_OR_EQUAL, "LESS_OR_EQUAL"}
        };
    }
}

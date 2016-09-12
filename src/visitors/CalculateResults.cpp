#include "CalculateResults.h"

CalculateResult::CalculateResult(CalculateResultType type) {
	this->type = type;
}

CalculateResultType CalculateResult::getType() {
	return type;
}

CalculateIntResult::CalculateIntResult(int value) : CalculateResult(INT_RESULT_TYPE) {
	this->value = value;
}

int CalculateIntResult::getValue() {
	return this->value;
}

CalculateNoneResult::CalculateNoneResult() : CalculateResult(NONE_RESULT_TYPE) {
}

CalculateErrorResult::CalculateErrorResult() : CalculateResult(ERROR_RESULT_TYPE) {
}

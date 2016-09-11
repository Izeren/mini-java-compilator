#pragma once

#include "CalculateResults.h"

CalculateResult::CalculateResult(ResultType type) {
	this.type = type;
}

ResultType CalculateResult::getType() {
	return type;
}

CalculateIntResult::CalculateIntResult(int value_) : value(value_) {
	super(IntResultType);
}

int CalculateIntResultgetValue() {
	return value;
}

CalculateNoneResult::CalculateNoneResult() {
	super(NoneResultType);
}

CalculateErrorResult::CalculateErrorResult() {
	super(ErrorResultType);
}

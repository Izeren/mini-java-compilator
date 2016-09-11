#include "IVisitorResult.h"

enum CalculateResultType {
	IntResultType, NoneResultType, ErrorResultType
};

class CalculateResult : public IVisitorResult {
	CalculateResultType type;

public:
	CalculateResult(ResultType type);
	
	ResultType getType();
};

class CalculateIntResult : public CalculateResult {
	int value;

public:
	CalculateIntResult(int value_);

	int getValue();
}

class CalculateNoneResult : public CalculateResult {
public:
	CalculateNoneResult();
}

class CalculateErrorResult : public CalculateResult {
public:
	CalculateErrorResult();
}

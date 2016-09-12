#include "IVisitorResult.h"

enum CalculateResultType {
	INT_RESULT_TYPE, NONE_RESULT_TYPE, ERROR_RESULT_TYPE
};

class CalculateResult : public IVisitorResult {
	CalculateResultType type;

public:
	CalculateResult(CalculateResultType type);
	
	CalculateResultType getType();
};

class CalculateIntResult : public CalculateResult {
	int value;

public:
	CalculateIntResult(int value);

	int getValue();
};

class CalculateNoneResult : public CalculateResult {
public:
	CalculateNoneResult();
};

class CalculateErrorResult : public CalculateResult {
public:
	CalculateErrorResult();
};

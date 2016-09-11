#include "IVisitorResult.h"

enum CalculateResultType {
	IntResulType, NoneResultType, ErrorResultType
};

class CalculateResult : public IVisitorResult {
	CalculateResultType type;

	Result(ResultType type) {
		this.type = type;
	}

	ResultType getType() {
		return type;
	}
};

class CalculateIntResult : public Result {
	int value;

	CalculateIntResult(int value_) : value(value_) {
		super(IntResultType);
	}

public:
	int getValue() {
		return value;
	}
}

class CalculateNoneResult : public Result {
	CalculateNoneResult() {
		super(NoneResultType);
	}
}

class CalculateErrorResult : public Result {
	int errorCode;

	CalculateErrorResult(int errorCode_) : errorCode(errorCode_) {
		super(ErrorResultType);
	}

public:
	void printError() {

	}
}

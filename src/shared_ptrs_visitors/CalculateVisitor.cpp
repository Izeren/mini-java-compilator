#include <iostream>

#include "IVisitor.h"
#include "CalculateVisitor.h"



//Expressions:
//-------------------------------------------------------------------------------------------------

void CCalculateVisitor::Visit(CIdExp &exp) {
	if (wasError) {
		return;
	}

	this->childResult = *(exp.address);
	this->isChildResultInteger = true;
}

void CCalculateVisitor::Visit(CIdPtrExp &exp) {
	if (wasError) {
		return;
	}

	this->childResult = *(exp.address);
	this->isChildResultInteger = true;
}

void CCalculateVisitor::Visit(CNumExp &exp) {
	if (wasError) {
		return;
	}

	this->childResult = exp.number;
	this->isChildResultInteger = true;
}

void CCalculateVisitor::Visit(COpExp &exp) {
	if (wasError) {
		return;
	}

	int leftResult;
	int rightResult;

	exp.leftOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	leftResult = this->childResult;

	exp.rightOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	rightResult = this->childResult;

	if (wasError) {
		return;
	}


	this->isChildResultInteger = true;
	switch (exp.operation) {
	case PLUS:
		this->childResult = leftResult + rightResult;
		break;
	case MINUS:
		this->childResult = leftResult - rightResult;
		break;
	case MULTIPLY:
		this->childResult = leftResult * rightResult;
		break;
		//case DIVISE:
		//	if (rightResult == 0) {
		//		this->wasError = true;
		//		break;
		//	} else {
		//		this->childResult = leftResult / rightResult;
		//		break;
		//	}
	}
}

void CCalculateVisitor::Visit(CLogExp &exp) {
	if (wasError) {
		return;
	}

	this->childResult = exp.variable;
	this->isChildResultInteger = true;
}

void CCalculateVisitor::Visit(CLogOpExp &exp) {
	if (wasError) {
		return;
	}

	int leftResult;
	int rightResult;

	exp.leftOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	leftResult = this->childResult;

	exp.rightOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	rightResult = this->childResult;

	if (wasError) {
		return;
	}

	this->isChildResultInteger = true;
	switch (exp.operation) {
	case AND:
		this->childResult = (leftResult && rightResult);
		break;
	case OR:
		this->childResult = (leftResult || rightResult);
		break;
	}
}

void CCalculateVisitor::Visit(CCompExp &exp) {
	if (wasError) {
		return;
	}

	int leftResult;
	int rightResult;

	exp.leftOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	leftResult = this->childResult;

	exp.rightOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	rightResult = this->childResult;

	if (wasError) {
		return;
	}

	this->isChildResultInteger = true;
	switch (exp.operation) {
	case GREATER:
		this->childResult = (leftResult > rightResult);
		break;
	case GREATER_OR_EQUAL:
		this->childResult = (leftResult >= rightResult);
		break;
	case LESS:
		this->childResult = (leftResult < rightResult);
		break;
	case LESS_OR_EQUAL:
		this->childResult = (leftResult <= rightResult);
		break;
	}
}

void CCalculateVisitor::Visit(CUnarMinusExp &exp) {
	if (wasError) {
		return;
	}

	int rightResult;

	exp.rightOperand.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	rightResult = this->childResult;

	this->childResult = -rightResult;
}



//Statements:
//-------------------------------------------------------------------------------------------------

void CCalculateVisitor::Visit(CAssignStm &stm) {
	if (wasError) {
		return;
	}

	stm.rightExpression.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	if (wasError) {
		return;
	}

	int rightResult = this->childResult;

	*(stm.leftExpression.get()->address) = rightResult;

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CAssignSubscriptStm &stm) {
	if (wasError) {
		return;
	}

	stm.valueExpression.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	if (wasError) {
		return;
	}

	int valueResult = this->childResult;

	*(stm.idExpression->address + stm.offset->number) = valueResult;

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CCompoundStm &stm) {
	if (wasError) {
		return;
	}

	stm.leftStatement.get()->Accept(*this);
	stm.rightStatement.get()->Accept(*this);

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CPrintStm &stm) {
	if (wasError) {
		return;
	}

	stm.expression.get()->Accept(*this);

	if (wasError) {
		return;
	}

	if (!this->isChildResultInteger) {
		this->wasError = true;
		return;
	}

	std::cout << this->childResult << '\n';
	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CSimpleStm &stm) {
	if (wasError) {
		return;
	}

	stm.statement.get()->Accept(*this);

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CIfStm &stm) {
	if (wasError) {
		return;
	}

	stm.conditionExpression.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	if (wasError) {
		return;
	}

	if (childResult) {
		stm.positiveStatement.get()->Accept(*this);
	}
	else {
		stm.negativeStatement.get()->Accept(*this);
	}

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CWhileStm &stm) {
	if (wasError) {
		return;
	}

	stm.conditionExpression.get()->Accept(*this);
	if (!this->isChildResultInteger) {
		wasError = true;
		return;
	}

	if (wasError) {
		return;
	}

	while (childResult) {
		stm.statement.get()->Accept(*this);
		stm.conditionExpression.get()->Accept(*this);

		if (!this->isChildResultInteger) {
			wasError = true;
			return;
		}

		if (wasError) {
			return;
		}
	}

	this->isChildResultInteger = false;
}



//Classes:
//-------------------------------------------------------------------------------------------------

void CCalculateVisitor::Visit(CType &stm) {
	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CField &stm) {
	if (wasError) {
		return;
	}

	stm.type.get()->Accept(*this);
	stm.id.get()->Accept(*this);

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CFieldList &stm) {
	if (wasError) {
		return;
	}

	if (stm.field) {
		stm.field.get()->Accept(*this);
	}
	if (stm.nextFields) {
		stm.nextFields.get()->Accept(*this);
	}

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CArgument &stm) {
	if (wasError) {
		return;
	}

	stm.type.get()->Accept(*this);
	stm.id.get()->Accept(*this);

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CArgumentList &stm) {
	if (wasError) {
		return;
	}

	if (stm.argument) {
		stm.argument.get()->Accept(*this);
	}
	if (stm.nextArguments) {
		stm.nextArguments.get()->Accept(*this);
	}

	this->isChildResultInteger = false;
}

void CCalculateVisitor::Visit(CMethod &stm) {
	if (wasError) {
		return;
	}

	stm.arguments.get()->Accept(*this);
	stm.statements.get()->Accept(*this);
}

void CCalculateVisitor::Visit(CMethodList &stm) {
	if (wasError) {
		return;
	}
	if (stm.method) {
		stm.method.get()->Accept(*this);
	}
	if (stm.nextMethods) {
		stm.nextMethods.get()->Accept(*this);
	}
}

void CCalculateVisitor::Visit(CClass &stm) {
	if (wasError) {
		return;
	}

	stm.parentClass.get()->Accept(*this);
	stm.id.get()->Accept(*this);
	stm.fields.get()->Accept(*this);
	stm.methods.get()->Accept(*this);
}

void CCalculateVisitor::Visit(CClassList &stm) {
	if (wasError) {
		return;
	}
	if (stm.cclass) {
		stm.cclass.get()->Accept(*this);
	}
	if (stm.nextClasses) {
		stm.nextClasses.get()->Accept(*this);
	}
}

void CCalculateVisitor::Visit(CMainMethod &stm) {
	if (wasError) {
		return;
	}
	stm.arguments.get()->Accept(*this);
	stm.statements->Accept(*this);
}

//void CCalculateVisitor::Visit(CMainClass &stm) {
//	if (wasError) {
//		return;
//	}
//	stm.id->Accept(*this);
//	stm.mainMethod->Accept(*this);
//}
//
//void CCalculateVisitor::Visit(CProgram &stm) {
//	if (wasError) {
//		return;
//	}
//	stm.mainClass->Accept(*this);
//	if (stm.classList) {
//		stm.classList->Accept(*this);
//	}
//}


int CCalculateVisitor::GetResult() {
	return childResult;
}
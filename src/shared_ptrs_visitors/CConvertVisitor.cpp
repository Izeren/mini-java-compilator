#include "CConvertVisitor.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

//std::unordered_map<TOperation, std::string> operationNames = {}

CConvertVisitor::CConvertVisitor() {
	//lastVisited = 0;
}

void CConvertVisitor::Visit(CPrintStm &stm) {

	this->code += "System.out.println(";
	if (stm.expression) {
		stm.expression->Accept(*this);
	}
	this->code += ")";

}

void CConvertVisitor::Visit(CCompoundStm &stm) {
	if (stm.leftStatement) {
		stm.leftStatement->Accept(*this);
	}
	if (stm.rightStatement) {
		stm.rightStatement->Accept(*this);
	}
}

void CConvertVisitor::Visit(COpExp &exp) {
	if (exp.leftOperand) {
		exp.leftOperand->Accept(*this);
	}
	this->code += " " + COpExp::stringOperations[exp.operation] + " ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CNumExp &exp) {
	this->code += std::to_string(exp.number);
}

void CConvertVisitor::Visit(CIdExp &exp) {
	this->code += exp.name;
}

void CConvertVisitor::Visit(CLogExp &exp) {
	if (exp.variable) {
		this->code += "true";
	} else {
		this->code += "false";
	}
}

void CConvertVisitor::Visit(CLogOpExp &exp) {
	if (exp.leftOperand) {
		exp.leftOperand->Accept(*this);
	}
	this->code += " " + exp.stringOperations[exp.operation] + " ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CCompExp &exp) {
	if (exp.leftOperand) {
		exp.leftOperand->Accept(*this);
	}
	this->code += " " + exp.stringOperations[exp.operation] + " ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CUnarMinusExp &exp) {
	this->code += "- ";
	if (exp.rightOperand) {
		exp.rightOperand->Accept(*this);
	}
}

void CConvertVisitor::Visit(CAssignStm &stm) {
	if (stm.leftExpression) {
		stm.leftExpression->Accept(*this);
	}
	this->code += " = ";
	if (stm.rightExpression) {
		stm.rightExpression->Accept(*this);
	}
}

void CConvertVisitor::Visit(CSimpleStm &stm) {
	if (stm.statement) {
		stm.statement->Accept(*this);
		this->code += ";\n";
	}
}

void CConvertVisitor::Visit(CIfStm &stm) {
	this->code += "if (";
	if (stm.conditionExpression) {
		stm.conditionExpression->Accept(*this);
	}
	this->code += ") {\n";
	if (stm.positiveStatement) {
		stm.positiveStatement->Accept(*this);
	}
	this->code += "}\n";
	if (stm.negativeStatement) {
		this->code += "else {\n";
		stm.negativeStatement->Accept(*this);
		this->code += "}\n";
	}
}

void CConvertVisitor::Visit(CWhileStm &stm) {
	this->code += "while (";
	if (stm.conditionExpression) {
		stm.conditionExpression->Accept(*this);
	}
	this->code += ") {\n";
	if (stm.statement) {
		stm.statement->Accept(*this);
	}
	this->code += "}\n";
}

std::string CConvertVisitor::GetResult() {
	return code;
}
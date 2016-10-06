#include "CConvertVisitor.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

//std::unordered_map<TOperation, std::string> operationNames = {}

CConvertVisitor::CConvertVisitor() {
	lastVisited = 0;
}

void CConvertVisitor::Visit(CPrintStm &stm) {

	this->code += "System.out.println(";
	stm.Accept(*this);
	this->code += ");\n";

}

void CConvertVisitor::Visit(CCompoundStm &stm) {
	if (stm.leftStatement) {
		stm.leftStatement->Accept(*this);
	}
	this->code += ";\n";
	if (stm.rightStatement) {
		stm.rightStatement->Accept(*this);
	}
	this->code += ";\n";
}

void CConvertVisitor::Visit(COpExp &exp) {
	if (exp.leftOperand) {
		exp.leftOperand->Accept(*this);
	}
	this->code += " " stringOperation[exp.operation] + " ";
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

void CConvertVisitor::Visit(CAssignStm &stm) {
	if (stm.leftExpression {
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
	}
}
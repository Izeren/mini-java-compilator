#include "CPrintVisitor.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

CPrintVisitor::CPrintVisitor() {
	lastVisited = 0;
}

void CPrintVisitor::Visit(CPrintStm &stm) {

	this->description = "";
	stm.expression->Accept(*this);
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=PrintStm]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CCompoundStm &stm) {
	this->description = "";
	stm.leftStatement->Accept(*this);
	std::string firstChildDescription = this->description;
	int leftId = lastVisited;
	this->description = "";
	stm.rightStatement->Accept(*this);
	std::string secondChildDescription = this->description;
	int rightId = lastVisited;
	this->description = firstChildDescription + secondChildDescription;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=CompoundStm]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(COpExp &exp) {
	this->description = "";
	exp.leftOperand->Accept(*this);
	std::string firstChildDescription = this->description;
	int leftId = lastVisited;
	int operationId = ++lastVisited;
	this->description = "";
	exp.rightOperand->Accept(*this);
	std::string secondChildDescription = this->description;
	int rightId = lastVisited;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(operationId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=OpExp]\n";
	this->description += "\t" + std::to_string(operationId) + "[label=Need to fix]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CNumExp &exp) {

	++lastVisited;
	this->description = "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=NumExp]\n";
	this->description += "\t" + std::to_string(lastVisited) + "[label=" + std::to_string(exp.number) + "]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CIdExp &exp) {

	++lastVisited;
	this->description = "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=IdExp]\n";
	this->description += "\t" + std::to_string(lastVisited) + "[label=" + exp.name + "]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CAssignStm &stm) {

	this->description = "";
	stm.leftExpression->Accept(*this);
	std::string firstChildDescription = this->description;
	int leftId = lastVisited;
	this->description = "";
	stm.rightExpression->Accept(*this);
	std::string secondChildDescription = this->description;
	int rightId = lastVisited;
	this->description = firstChildDescription + secondChildDescription;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=AssignStm]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CSimpleStm &stm) {

	this->description = "";
	stm.statement->Accept(*this);
	int stmId = lastVisited;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(stmId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=CompoundStm]\n";
	++lastVisited;
}

std::string CPrintVisitor::GetResult() {
	return description;
}
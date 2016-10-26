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
	this->description = "";
	this->description += firstChildDescription;
	this->description += "\t" + std::to_string(operationId) + "[label=" + exp.stringOperations[exp.operation] + "]\n";
	this->description += secondChildDescription;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(operationId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=OpExp]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CNumExp &exp) {

	++lastVisited;
	this->description = "\t" + std::to_string(lastVisited) + "[label=" + std::to_string(exp.number) + "]\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=NumExp]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CIdExp &exp) {

	++lastVisited;
	this->description = "\t" + std::to_string(lastVisited) + "[label=" + exp.name + "]\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=IdExp]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CLogExp &exp) {

	++lastVisited;
	this->description = "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=LogExp]\n";
	this->description += "\t" + std::to_string(lastVisited) + "[label=" + std::to_string(exp.variable) + "]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CLogOpExp &exp) {
	this->description = "";
	exp.leftOperand->Accept(*this);
	std::string firstChildDescription = this->description;
	int leftId = lastVisited;
	int operationId = ++lastVisited;
	this->description = "";
	exp.rightOperand->Accept(*this);
	std::string secondChildDescription = this->description;
	int rightId = lastVisited;
	this->description = "";
	this->description += firstChildDescription;
	this->description += "\t" + std::to_string(operationId) + "[label=" + exp.stringOperations[exp.operation] + "]\n";
	this->description += secondChildDescription;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(operationId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=LogOpExp]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CCompExp &exp) {
	this->description = "";
	exp.leftOperand->Accept(*this);
	std::string firstChildDescription = this->description;
	int leftId = lastVisited;
	int operationId = ++lastVisited;
	this->description = "";
	exp.rightOperand->Accept(*this);
	std::string secondChildDescription = this->description;
	int rightId = lastVisited;
	this->description = "";
	this->description += firstChildDescription;
	this->description += "\t" + std::to_string(operationId) + "[label=" + exp.stringOperations[exp.operation] + "]\n";
	this->description += secondChildDescription;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(operationId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=CompExp]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CUnarMinusExp &exp) {
	this->description = "";
	exp.rightOperand->Accept(*this);
	std::string childDescription = this->description;
	int rightId = lastVisited;
	this->description = "";
	this->description += childDescription;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=UnarMinusExp]\n";
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

void CPrintVisitor::Visit(CIfStm &stm) {
	this->description = "";
	stm.conditionExpression->Accept(*this);
	std::string conditionDescription = this->description;
	int conditionId = lastVisited;
	this->description = "";
	stm.positiveStatement->Accept(*this);
	std::string positiveDescription = this->description;
	int positiveId = lastVisited;
	this->description = "";
	stm.negativeStatement->Accept(*this);
	std::string negativeDescription = this->description;
	int negativeId = lastVisited;
	this->description = conditionDescription + positiveDescription + negativeDescription;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(conditionId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(positiveId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(negativeId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=IfStm]\n";
	++lastVisited;
}

void CPrintVisitor::Visit(CWhileStm &stm) {
	this->description = "";
	stm.conditionExpression->Accept(*this);
	std::string conditionDescription = this->description;
	int conditionId = lastVisited;
	this->description = "";
	stm.statement->Accept(*this);
	std::string statementDescription = this->description;
	int statementId = lastVisited;
	this->description = conditionDescription + statementDescription;
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(conditionId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(statementId) + "\n";
	this->description += "\t" + std::to_string(lastVisited + 1) + "[label=IfStm]\n";
	++lastVisited;
}

std::string CPrintVisitor::GetResult() {
	return description;
}
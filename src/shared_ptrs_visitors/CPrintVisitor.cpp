#include "CPrintVisitor.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

void ChildrenAnswers::PushBack(std::string description, int id) {
	this->descriptions.push_back(description);
	this->ids.push_back(id);
}

CPrintVisitor::CPrintVisitor() {
	lastVisited = 0;
}

ChildrenAnswers CPrintVisitor::VisitChildren(std::vector<INode*> children) {
	ChildrenAnswers answers = ChildrenAnswers();
	for (int i = 0; i < children.size(); i++) {
		children[i]->Accept(*this);
		answers.PushBack(this->description, lastVisited);
	}
	return answers;
}

void CPrintVisitor::AddChildrenDescriptions(ChildrenAnswers answers) {
	for (int i = 0; i < answers.descriptions.size(); i++) {
		this->description += answers.descriptions[i];
	}
}

void CPrintVisitor::AddChildrenIds(ChildrenAnswers answers) {
	for (int i = 0; i < answers.descriptions.size(); i++) {
		AddArrow(answers.ids[i]);
	}
}

void CPrintVisitor::AddChildrenAnswers(ChildrenAnswers answers) {
	this->description = "";
	AddChildrenDescriptions(answers);
	AddChildrenIds(answers);
}

std::string CPrintVisitor::ConstructLabel(std::string label, int id) {
	return "\t" + std::to_string(id) + "[label=" + label + "]\n";
}

void CPrintVisitor::AddLabel(std::string label) {
	this->description += ConstructLabel(label, lastVisited + 1);
}

void CPrintVisitor::AddArrow(int child_id) {
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(child_id) + "\n";
}

void CPrintVisitor::Visit(CPrintStm &stm) {
	this->description = "";
	stm.expression->Accept(*this);
	AddArrow(lastVisited);
	AddLabel("PrintStm");
	++lastVisited;
}

void CPrintVisitor::Visit(CCompoundStm &stm) {
	std::vector<INode*> children = { stm.leftStatement.get(), stm.rightStatement.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("CompoundStm");
	++lastVisited;
}

void CPrintVisitor::Visit(COpExp &exp) {
	std::vector<INode*> children = { exp.leftOperand.get(), exp.rightOperand.get() };
	ChildrenAnswers answers = VisitChildren(children);

	int operationId = ++lastVisited;
	std::string operationDescription = ConstructLabel(exp.stringOperations[exp.operation], operationId);
	answers.PushBack(operationDescription, operationId);

	AddChildrenAnswers(answers);
	AddLabel("OpExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CNumExp &exp) {
	++lastVisited;
	this->description = ConstructLabel(std::to_string(exp.number), lastVisited);
	AddArrow(lastVisited);
	AddLabel("NumExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CIdExp &exp) {
	++lastVisited;
	this->description = ConstructLabel(exp.name, lastVisited);
	AddArrow(lastVisited);
	AddLabel("IdExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CLogExp &exp) {
	++lastVisited;
	this->description = ConstructLabel(std::to_string(exp.variable), lastVisited);
	AddArrow(lastVisited);
	AddLabel("LogExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CLogOpExp &exp) {
	std::vector<INode*> children = { exp.leftOperand.get(), exp.rightOperand.get() };
	ChildrenAnswers answers = VisitChildren(children);

	int operationId = ++lastVisited;
	std::string operationDescription = ConstructLabel(exp.stringOperations[exp.operation], operationId);
	answers.PushBack(operationDescription, operationId);

	AddChildrenAnswers(answers);
	AddLabel("LogOpExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CCompExp &exp) {
	std::vector<INode*> children = { exp.leftOperand.get(), exp.rightOperand.get() };
	ChildrenAnswers answers = VisitChildren(children);

	int operationId = ++lastVisited;
	std::string operationDescription = ConstructLabel(exp.stringOperations[exp.operation], operationId);
	answers.PushBack(operationDescription, operationId);

	AddChildrenAnswers(answers);
	AddLabel("CompExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CUnarMinusExp &exp) {
	std::vector<INode*> children = { exp.rightOperand.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("UnarMinusExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CAssignStm &stm) {
	std::vector<INode*> children = { stm.leftExpression.get(), stm.rightExpression.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("AssignStm");
	++lastVisited;
}

void CPrintVisitor::Visit(CSimpleStm &stm) {
	std::vector<INode*> children = { stm.statement.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("CompoundStm");
	++lastVisited;
}

void CPrintVisitor::Visit(CIfStm &stm) {
	std::vector<INode*> children = { 
		stm.conditionExpression.get(), 
		stm.positiveStatement.get(), 
		stm.negativeStatement.get() 
	};
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("IfStm");
	++lastVisited;
}

void CPrintVisitor::Visit(CWhileStm &stm) {
	std::vector<INode*> children = { stm.conditionExpression.get(), stm.statement.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("WhileStm");
	++lastVisited;
}

std::string CPrintVisitor::GetResult() {
	return description;
}
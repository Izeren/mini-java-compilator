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
		if ( children[i] ) {
			children[i]->Accept(*this);
			answers.PushBack(this->description, lastVisited);
			this->description = "";
		}
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
	return "\t" + std::to_string(id) + "[label=\"" + label + "\"]\n";
}

void CPrintVisitor::AddLabel(std::string label) {
	this->description += ConstructLabel(label, lastVisited + 1);
}

void CPrintVisitor::AddArrow(int child_id) {
	this->description += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(child_id) + "\n";
}




//Expressions:
//-------------------------------------------------------------------------------------------------

void CPrintVisitor::Visit(CIdExp &exp) {
	++lastVisited;
	std::cout << exp.name;
	this->description = ConstructLabel(exp.name, lastVisited);
	AddArrow(lastVisited);
	AddLabel("IdExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CIdPtrExp &exp) {
	++lastVisited;
	this->description = ConstructLabel(exp.name, lastVisited);
	AddArrow(lastVisited);
	AddLabel("IdPtrExp");
	++lastVisited;
}

void CPrintVisitor::Visit(CNumExp &exp) {
	++lastVisited;
	this->description = ConstructLabel(std::to_string(exp.number), lastVisited);
	AddArrow(lastVisited);
	AddLabel("NumExp");
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

void CPrintVisitor::Visit(CGetLengthExp &exp)
{
	std::vector<INode*> children = { exp.arrayIdentifier.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("Length");
	++lastVisited;
}

void CPrintVisitor::Visit(CGetFieldExp &exp)
{
	std::vector<INode*> children = { exp.classOwner.get(), exp.field.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("Field");
	++lastVisited;	
}

void CPrintVisitor::Visit(CCallMethodExp &exp)
{
	std::vector<INode*> children = { exp.objectExpression.get(), exp.methodName.get(), exp.args.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("CallMethod");
	++lastVisited;	
}

void CPrintVisitor::Visit(CExpList &stm) {
	std::vector<INode*> children;
	for (int index = 0; index < stm.exps.size(); ++index) {
		children.push_back(stm.exps[index].get());
	}
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("ExpList");
	++lastVisited;
}

void CPrintVisitor::Visit(CNegativeExpression &exp)
{
	std::vector<INode*> children = { exp.expression.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("Negative");
	++lastVisited;	
}

void CPrintVisitor::Visit(CArrayExpression &exp)
{
	std::vector<INode*> children = { exp.lengthExpression.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("Array");
	++lastVisited;	
}

void CPrintVisitor::Visit(CNewIdentifier &exp)
{
	std::vector<INode*> children = { exp.identifier.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("NewIdentifier");
	++lastVisited;	
}

void CPrintVisitor::Visit(CGetFieldByThisExpression &exp)
{
	AddLabel("GetFieldByThis");
	++lastVisited;
}

void CPrintVisitor::Visit(CByIndexExpression &exp)
{
	std::vector<INode*> children = { exp.identifier.get(), exp.indexExpression.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("ElementByIndex");
	++lastVisited;	
}

//Statements:
//-------------------------------------------------------------------------------------------------

void CPrintVisitor::Visit(CAssignStm &stm) {
	std::vector<INode*> children = { stm.leftExpression.get(), stm.rightExpression.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("AssignStm");
	++lastVisited;
}

void CPrintVisitor::Visit(CAssignSubscriptStm &stm) {
	std::vector<INode*> children = { stm.idExpression.get(), stm.offset.get(), stm.valueExpression.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("AssignSubscriptStm");
	++lastVisited;
}

void CPrintVisitor::Visit(CCompoundStm &stm) {
	std::vector<INode*> children = { stm.leftStatement.get(), stm.rightStatement.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("CompoundStm");
	++lastVisited;
}

void CPrintVisitor::Visit(CPrintStm &stm) {
	this->description = "";
	stm.expression->Accept(*this);
	AddArrow(lastVisited);
	AddLabel("PrintStm");
	++lastVisited;
}

void CPrintVisitor::Visit(CIfStm &stm) {
	std::vector<INode*> children = { 
		stm.conditionExpression.get(), 
		stm.positiveStatement.get()
	};
	if (stm.negativeStatement) {
		children.push_back(stm.negativeStatement.get());
	}
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



//Classes:
//-------------------------------------------------------------------------------------------------

void CPrintVisitor::Visit(CType &stm) {
	if (stm.isPrimitive) {
		AddLabel(CType::typeNames[stm.type]);
	} else {
		std::vector<INode*> children = { stm.name.get() };
		AddChildrenAnswers(VisitChildren(children));
		AddLabel("Type");
	}
	++lastVisited;
}

void CPrintVisitor::Visit(CField &stm) {
	std::vector<INode*> children = { stm.type.get(), stm.id.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("Field");
	++lastVisited;
}

void CPrintVisitor::Visit(CFieldList &stm) {
	std::vector<INode*> children;
	for (int index = 0; index < stm.fields.size(); ++index) {
		children.push_back(stm.fields[index].get());
	}
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("FieldList");
	++lastVisited;
}

void CPrintVisitor::Visit(CArgument &stm) {
	std::vector<INode*> children = { stm.type.get(), stm.id.get() };
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("Argument");
	++lastVisited;
}

void CPrintVisitor::Visit(CArgumentList &stm) {
	std::vector<INode*> children;
	for (int index = 0; index < stm.arguments.size(); ++index) {
		children.push_back(stm.arguments[index].get());
	}
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("ArgumentList");
	++lastVisited;
}

void CPrintVisitor::Visit(CMethod &stm) {
	std::vector<INode*> children = { stm.returnType.get(), stm.returnExp.get(), stm.arguments.get(), stm.vars.get(), stm.statements.get() };
	ChildrenAnswers answers = VisitChildren(children);

	AddChildrenAnswers(answers);
	if (stm.isPublic) {
		AddLabel("PublicMethod");
	} else {
		AddLabel("PrivateMethod");
	}
	++lastVisited;
}

void CPrintVisitor::Visit(CMethodList &stm) {
	std::vector<INode*> children;
	for (int index = 0; index < stm.methods.size(); ++index) {
		children.push_back(stm.methods[index].get());
	}
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("MethodList");
	++lastVisited;
}

void CPrintVisitor::Visit(CClass &stm) {
	std::vector<INode*> children = { stm.parentClass.get(), stm.id.get(), stm.fields.get(), stm.methods.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("Class");
	++lastVisited;
}

void CPrintVisitor::Visit(CClassList &stm) {
	std::vector<INode*> children;
	for (int index = 0; index < stm.classes.size(); ++index) {
		children.push_back(stm.classes[index].get());
	}
	AddChildrenAnswers(VisitChildren(children));
	AddLabel("ClassList");
	++lastVisited;
}

void CPrintVisitor::Visit(CMainMethod &stm) {
	std::cout << "Point\n";
	std::vector<INode*> children = { stm.returnType.get(), stm.args.get(), stm.vars.get(), stm.statements.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("MainMethod");
	++lastVisited;
}

void CPrintVisitor::Visit(CMainClass &stm) {
	std::vector<INode*> children = { stm.id.get(), stm.mainMethod.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("MainClass");
	++lastVisited;
}

void CPrintVisitor::Visit(CProgram &stm) {
	std::vector<INode*> children = { stm.mainClass.get(), stm.classList.get() };
	ChildrenAnswers answers = VisitChildren(children);
	AddChildrenAnswers(answers);
	AddLabel("Program");
	++lastVisited;
}



std::string CPrintVisitor::GetResult() {
	return "digraph G{\ngraph[ordering=\"out\"];\n" + description + "}\n";
}
#include "CPrintVisitor.h"
#include "CPrintResults.h"
#include <iostream>
#include <algorithm>

CPrintVisitor::CPrintVisitor() {
	lastVisited = 0;
}

IVisitorResult* CPrintVisitor::Visit(CPrintStm *stm) {

	CPrintResults* result = reinterpret_cast<CPrintResults*>(stm->expression->Accept(this));
	std::string subdescription = result->getDescription();
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + "[label=PrintStm]\n";
	++lastVisited;
	return new CPrintResults(subdescription);

}

IVisitorResult* CPrintVisitor::Visit(CCompoundStm *stm) {

	CPrintResults* result = reinterpret_cast<CPrintResults*>(stm->leftStatement->Accept(this));
	std::string subdescription = result->getDescription();
	int leftId = lastVisited;
	result = reinterpret_cast<CPrintResults*>(stm->rightStatement->Accept(this));
	subdescription += result->getDescription();
	int rightId = lastVisited;
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + "[label=CompoundStm]\n";
	++lastVisited;
	return new CPrintResults(subdescription);

}

IVisitorResult* CPrintVisitor::Visit(COpExp *exp) {

	CPrintResults* result = reinterpret_cast<CPrintResults*>(exp->leftOperand->Accept(this));
	std::string subdescription = result->getDescription();
	int leftId = lastVisited;
	int operationId = ++lastVisited;
	result = reinterpret_cast<CPrintResults*>(exp->rightOperand->Accept(this));
	subdescription += result->getDescription();
	int rightId = lastVisited;
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(operationId) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + "[label=OpExp]\n";
	std::string operationName;
	switch (exp->operation) {
		case PLUS: {
			operationName = "PLUS";
			break;
		}
		case MINUS: {
			operationName = "MINUS";
			break;
		}
		case MULTIPLY: {
			operationName = "MULTIPLY";
			break;
		}
		case DIVISE: {
			operationName = "DIVISE";
		}
		default: {
			operationName = "UnknownOperation";
			break;
		}
	}
	subdescription += "\t" + std::to_string(operationId) + "[label=" + operationName + "]\n";
	++lastVisited;
	return new CPrintResults(subdescription);

}

IVisitorResult* CPrintVisitor::Visit(CNumExp *exp) {

	++lastVisited;
	std::string subdescription = "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + "[label=NumExp]\n";
	subdescription += "\t" + std::to_string(lastVisited) + "[label=" + std::to_string(exp->number) + "]\n";
	++lastVisited;
	return new CPrintResults(subdescription);	
}

IVisitorResult* CPrintVisitor::Visit(CIdExp *exp) {

	++lastVisited;
	std::string subdescription = "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(lastVisited) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + "[label=IdExp]\n";
	subdescription += "\t" + std::to_string(lastVisited) + "[label=" + exp->name + "]\n";
	++lastVisited;
	return new CPrintResults(subdescription);
}

IVisitorResult* CPrintVisitor::Visit(CAssignStm *stm) {

	CPrintResults* result = reinterpret_cast<CPrintResults*>(stm->leftExpression->Accept(this));
	std::string subdescription = result->getDescription();
	int leftId = lastVisited;
	result = reinterpret_cast<CPrintResults*>(stm->rightExpression->Accept(this));
	subdescription += result->getDescription();
	int rightId = lastVisited;
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(leftId) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(rightId) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + "[label=AssignStm]\n";
	++lastVisited;
	return new CPrintResults(subdescription);
}

IVisitorResult* CPrintVisitor::Visit(CSimpleStm *stm) {

	CPrintResults* result = reinterpret_cast<CPrintResults*>(stm->statement->Accept(this));
	std::string subdescription = result->getDescription();
	int stmId = lastVisited;
	subdescription += "\t" + std::to_string(lastVisited + 1) + " -> " + std::to_string(stmId) + "\n";
	subdescription += "\t" + std::to_string(lastVisited + 1) + "[label=CompoundStm]\n";
	++lastVisited;
	return new CPrintResults(subdescription);

}
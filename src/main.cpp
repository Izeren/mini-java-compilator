#include "nodes/expressions/IExpression.h"
#include "nodes/statements/IStatement.h"
#include "visitors/CPrintVisitor.h"
#include "visitors/CalculateVisitor.h"
#include "visitors/CPrintResults.h"

#include <iostream>

int main() {

	CCompoundStm *tree = new CCompoundStm();
	tree->leftStatement = new CAssignStm();
	tree->leftStatement->leftExpression = new CIdExp("a");
	tree->leftStatement->rightExpression = new COpExp();
	tree->leftStatement->rightExpression->leftOperand = new CNumExp(5);
	tree->leftStatement->rightExpression->rightOperand = new CNumExp(3);
	tree->leftStatement->rightExpression->operation = PLUS;
	tree->rightStatement = new CPrintStm();
	tree->rightStatement->expression = new CIdExp("a");

	CPrintVisitor *printVisitor = new CPrintVisitor();
	CPrintResults result = tree->Accept(printVisitor);
	std::cout << result.getDescription() << "\n";


	// delete tree->rightStatement->expression;
	// delete tree->rightStatement;
	// delete tree->leftStatement->rightExpression->leftOperand;
	// delete tree->leftStatement->rightExpression->rightOperand;
	// delete tree->leftStatement->leftExpression;
	// delete tree->leftStatement->rightExpression;
	// delete tree->leftStatement;
	// delete tree;

	return 0;
}
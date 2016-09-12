#include <stdlib.h>
#include "nodes/expressions/IExpression.h"
#include "nodes/statements/IStatement.h"
#include "nodes/expressions/COpExp.h"
#include "nodes/expressions/CNumExp.h"
#include "nodes/expressions/CIdExp.h"
#include "nodes/statements/CAssignStm.h"
#include "nodes/statements/CCompoundStm.h"
#include "nodes/statements/CPrintStm.h"
#include "visitors/CPrintVisitor.h"
#include "visitors/CPrintResults.h"
#include "visitors/CalculateVisitor.h"
#include "visitors/CalculateResults.h"

#include <fstream>
#include <iostream>

CCompoundStm* buildTree() {
	CCompoundStm *tree= new CCompoundStm(
			reinterpret_cast<IStatement *>(new CAssignStm(
				new CIdExp("a"),
				reinterpret_cast<IExpression *>(new COpExp(
					reinterpret_cast<IExpression *>(new CNumExp(5)),
					reinterpret_cast<IExpression *>(new CNumExp(3)),
					PLUS
				))
			)),
			reinterpret_cast<IStatement *>(new CPrintStm(
				reinterpret_cast<IExpression *>(new CIdExp("a"))
			))
		);

	return tree;
}

COpExp *buildCaculatableExpression() {
	int *a = new int;
	int *b = new int;
	*a = 5;
	*b = 6;
	COpExp *expression = new COpExp(
		reinterpret_cast<IExpression *>(new COpExp(
			reinterpret_cast<IExpression *>(new CIdExp("a", a)),
			reinterpret_cast<IExpression *>(new CNumExp(3)),
			PLUS
		)),
		reinterpret_cast<IExpression *>(new COpExp(
			reinterpret_cast<IExpression *>(new CIdExp("b", b)),
			reinterpret_cast<IExpression *>(new CIdExp("a", a)),
			MINUS
		)),
		MULTIPLY
	);
	return expression;
}

void freeExpression(IExpression *expression) {
	delete expression;
}

void cutDownTree(INode *tree) {
	delete tree;
}

void testPrintVisitor() {

	// INode *tree = buildTree();
	INode *tree = buildCaculatableExpression();

	CPrintVisitor *printVisitor = new CPrintVisitor();
	CPrintResults *result = reinterpret_cast<CPrintResults *>(tree->Accept(printVisitor));

	std::ofstream out("output.txt");
	out << "digraph G{\ngraph[ordering=\"out\"];\n" << result->getDescription() << "}\n"<< "\n";

	out.close();

	delete printVisitor;
	cutDownTree(tree);

}

void testCalculateVisitor() {

	COpExp *expression = buildCaculatableExpression();

	CCalculateVisitor *calculateVisitor = new CCalculateVisitor();
	CalculateIntResult *result = reinterpret_cast<CalculateIntResult *>(expression->Accept(calculateVisitor));

	int intResult = result->getValue();
	std::cout << intResult << "\n";

	delete calculateVisitor;
	freeExpression(reinterpret_cast<COpExp *>(expression));

}

int main() {

	testPrintVisitor();
	testCalculateVisitor();
	
	return 0;
}
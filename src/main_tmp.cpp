#include "shared_ptrs_visitors\CPrintVisitor.h"
#include "shared_ptrs_visitors\IVisitor.h"
#include "shared_ptrs_nodes\Expressions.h"
#include "shared_ptrs_nodes\INode.h"
#include "shared_ptrs_nodes\Statements.h"

#include <fstream>
#include <iostream>

CCompoundStm* buildTree() {
	CCompoundStm* tree = new CCompoundStm(
		std::shared_ptr<IStatement>(new CAssignStm(
			std::shared_ptr<CIdExp>(new CIdExp("a")),
			std::shared_ptr<IExpression>(new COpExp(
				std::shared_ptr<IExpression>(new CNumExp(5)),
				std::shared_ptr<IExpression>(new CNumExp(3)),
				PLUS
			))
		)),
		std::shared_ptr<IStatement>(new CPrintStm(
			std::shared_ptr<IExpression>(new CIdExp("a"))
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
		std::shared_ptr<IExpression>(new COpExp(
			std::shared_ptr<IExpression>(new CIdExp("a", a)),
			std::shared_ptr<IExpression>(new CNumExp(3)),
			PLUS
		)),
		std::shared_ptr<IExpression>(new COpExp(
			std::shared_ptr<IExpression>(new CIdExp("b", b)),
			std::shared_ptr<IExpression>(new CIdExp("a", a)),
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

	 INode* tree = buildTree();
	// INode *tree = buildCaculatableExpression();

	CPrintVisitor printVisitor = CPrintVisitor();
	tree->Accept(printVisitor);

	std::ofstream out("output.txt");
	out << "digraph G{\ngraph[ordering=\"out\"];\n" << printVisitor.getDescription() << "}\n" << "\n";

	out.close();

	//delete printVisitor;
	cutDownTree(tree);

}


int main()
{
	testPrintVisitor();
    return 0;
}


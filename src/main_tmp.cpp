#include "shared_ptrs_visitors\CPrintVisitor.h"
#include "shared_ptrs_visitors\IVisitor.h"
#include "shared_ptrs_nodes\Expressions.h"
#include "stdafx.h"

#include "shared_ptrs_nodes\INode.h"
#include "shared_ptrs_nodes\Statements.h"
#include "shared_ptrs_visitors\CalculateVisitor.h"
#include "shared_ptrs_visitors\CConvertVisitor.h"

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

CCompoundStm* buildDifficultTree() {
	int *i = new int;
	*i = 0;
	CCompoundStm* tree = new CCompoundStm(
		std::shared_ptr<CCompoundStm>(new CCompoundStm(
			std::shared_ptr<CSimpleStm>(new CSimpleStm(
				std::shared_ptr<CAssignStm>(new CAssignStm(
					std::shared_ptr<CIdExp>(new CIdExp("i", i)),
					std::shared_ptr<IExpression>(new CNumExp(1))
				))
			)),
			std::shared_ptr<CWhileStm>(new CWhileStm(
				std::shared_ptr<CLogOpExp>(new CLogOpExp(
					std::shared_ptr<CCompExp>(new CCompExp(
						std::shared_ptr<CIdExp>(new CIdExp("i", i)),
						std::shared_ptr<IExpression>(new CNumExp(4)),
						LESS
					)),
					std::shared_ptr<CLogExp>(new CLogExp(true))
				)),
				std::shared_ptr<CSimpleStm>(new CSimpleStm(
					std::shared_ptr<CAssignStm>(new CAssignStm(
						std::shared_ptr<CIdExp>(new CIdExp("i", i)),
						std::shared_ptr<IExpression>(new COpExp(
							std::shared_ptr<IExpression>(new CIdExp("i", i)),
							std::shared_ptr<IExpression>(new CNumExp(1)),
							PLUS
						))
					))
				))
			))
		)),
		std::shared_ptr<CIfStm>(new CIfStm(
			std::shared_ptr<CLogExp>(new CLogExp(false)),
			std::shared_ptr<CSimpleStm>(new CSimpleStm(
				std::shared_ptr<CAssignStm>(new CAssignStm(
					std::shared_ptr<CIdExp>(new CIdExp("i", i)),
					std::shared_ptr<IExpression>(new COpExp(
						std::shared_ptr<IExpression>(new CIdExp("i", i)),
						std::shared_ptr<IExpression>(new CNumExp(2)),
						MULTIPLY
					))
				))
			)),
			std::shared_ptr<CSimpleStm>(new CSimpleStm(
				std::shared_ptr<CAssignStm>(new CAssignStm(
					std::shared_ptr<CIdExp>(new CIdExp("i", i)),
					std::shared_ptr<IExpression>(new CUnarMinusExp(
						std::shared_ptr<IExpression>(new CIdExp("i", i))
					))
				))
			))
		))
	);

	return tree;
}

void freeExpression(IExpression *expression) {
	delete expression;
}

void cutDownTree(INode *tree) {
	delete tree;
}

void testPrintVisitor() {

	INode* tree = buildTree();

	CPrintVisitor printVisitor = CPrintVisitor();
	tree->Accept(printVisitor);

	std::ofstream out("output.txt");
	out << "digraph G{\ngraph[ordering=\"out\"];\n" << printVisitor.GetResult() << "}\n" << "\n";

	out.close();

	cutDownTree(tree);
}

void testCalculateVisitor() {

	COpExp *expression = buildCaculatableExpression();

	CCalculateVisitor calculateVisitor = CCalculateVisitor();
	expression->Accept(calculateVisitor);

	int intResult = calculateVisitor.GetResult();
	std::cout << intResult << "\n";

	freeExpression(reinterpret_cast<COpExp *>(expression));

}

void testConvertVisitor() {

	INode* tree = buildDifficultTree();

	CConvertVisitor convertVisitor = CConvertVisitor();
	tree->Accept(convertVisitor);

	std::string stringResult = convertVisitor.GetResult();
	std::cout << stringResult << "\n";

	freeExpression(reinterpret_cast<COpExp *>(tree));

}


int main()
{
	testPrintVisitor();
	testCalculateVisitor();
	testConvertVisitor();

    return 0;
}


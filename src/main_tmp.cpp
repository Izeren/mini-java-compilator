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
		(IStatement*)(new CAssignStm(
			new CIdExp("a"),
			(IExpression*)(new COpExp(
				(IExpression*)(new CNumExp(5)),
				(IExpression*)(new CNumExp(3)),
				PLUS
			))
		)),
		(IStatement*)(new CPrintStm(
			(IExpression*)(new CIdExp("a"))
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
		(IExpression*)(new COpExp(
			(IExpression*)(new CIdExp("a", a)),
			(IExpression*)(new CNumExp(3)),
			PLUS
		)),
		(IExpression*)(new COpExp(
			(IExpression*)(new CIdExp("b", b)),
			(IExpression*)(new CIdExp("a", a)),
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
		(CCompoundStm*)(new CCompoundStm(
			(CSimpleStm*)(new CSimpleStm(
				(CAssignStm*)(new CAssignStm(
					(CIdExp*)(new CIdExp("i", i)),
					(IExpression*)(new CNumExp(1))
				))
			)),
			(CWhileStm*)(new CWhileStm(
				(CLogOpExp*)(new CLogOpExp(
					(CCompExp*)(new CCompExp(
						(CIdExp*)(new CIdExp("i", i)),
						(IExpression*)(new CNumExp(4)),
						LESS
					)),
					(CLogExp*)(new CLogExp(true))
				)),
				(CSimpleStm*)(new CSimpleStm(
					(CAssignStm*)(new CAssignStm(
						(CIdExp*)(new CIdExp("i", i)),
						(IExpression*)(new COpExp(
							(IExpression*)(new CIdExp("i", i)),
							(IExpression*)(new CNumExp(1)),
							PLUS
						))
					))
				))
			))
		)),
		(CIfStm*)(new CIfStm(
			(CLogExp*)(new CLogExp(false)),
			(CSimpleStm*)(new CSimpleStm(
				(CAssignStm*)(new CAssignStm(
					(CIdExp*)(new CIdExp("i", i)),
					(IExpression*)(new COpExp(
						(IExpression*)(new CIdExp("i", i)),
						(IExpression*)(new CNumExp(2)),
						MULTIPLY
					))
				))
			)),
			(CSimpleStm*)(new CSimpleStm(
				(CAssignStm*)(new CAssignStm(
					(CIdExp*)(new CIdExp("i", i)),
					(IExpression*)(new CUnarMinusExp(
						(IExpression*)(new CIdExp("i", i))
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

	freeExpression(reinterpret_cast<COpExp*>(expression));

}

void testConvertVisitor() {

	INode* tree = buildDifficultTree();

	CConvertVisitor convertVisitor = CConvertVisitor();
	tree->Accept(convertVisitor);

	std::string stringResult = convertVisitor.GetResult();
	std::cout << stringResult << "\n";

	freeExpression(reinterpret_cast<COpExp*>(tree));

}


int main()
{
	testPrintVisitor();
	testCalculateVisitor();
	testConvertVisitor();

    return 0;
}


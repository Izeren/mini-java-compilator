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
// #include "visitors/CalculateVisitor.h"
#include "visitors/CPrintResults.h"

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

void cutDownTree(CCompoundStm *tree) {
	delete tree;
}

int main() {

	CCompoundStm *tree = buildTree();

	CPrintVisitor *printVisitor = new CPrintVisitor();
	CPrintResults *result = reinterpret_cast<CPrintResults *>(tree->Accept(printVisitor));

	std::ofstream out("output.txt");
	out << "digraph {\n" << result->getDescription() << "}\n"<< "\n";

	out.close();

	cutDownTree(tree);

	return 0;
}
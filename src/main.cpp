#include <stdlib.h>
#include "nodes/expressions/IExpression.h"
#include "nodes/statements/IStatement.h"
#include "nodes/expressions/COpExp.h"
#include "nodes/expressions/CNumExp.h"
#include "nodes/expressions/CIdExp.h"
#include "nodes/statements/CAssignStm.h"
#include "nodes/statements/CCompoundStm.h"
#include "nodes/statements/CPrintStm.h"
// #include "visitors/CPrintVisitor.h"
// #include "visitors/CalculateVisitor.h"
// #include "visitors/CPrintResults.h"


#include <iostream>

int main() {

	CCompoundStm *tree = new CCompoundStm(
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

	// CPrintVisitor *printVisitor = new CPrintVisitor();
	// CPrintResults result = tree->Accept(printVisitor);
	// std::cout << result.getDescription() << "\n";


	delete tree;

	return 0;
}
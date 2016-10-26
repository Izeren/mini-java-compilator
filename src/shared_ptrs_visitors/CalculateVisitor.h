#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "IVisitor.h"
#include "../shared_ptrs_nodes/Statements.h"
#include "../shared_ptrs_nodes/Expressions.h"

class CCalculateVisitor : public IVisitor {
public:
	void Visit(CPrintStm &stm) override;
	void Visit(CCompoundStm &stm) override;
	void Visit(COpExp &exp) override;
	void Visit(CNumExp &exp) override;
	void Visit(CIdExp &exp) override;
	void Visit(CLogExp &exp) override;
	void Visit(CLogOpExp &exp) override;
	void Visit(CCompExp &exp) override;
	void Visit(CUnarMinusExp &exp) override;
	void Visit(CAssignStm &exp) override;
	void Visit(CSimpleStm &exp) override;
	void Visit(CIfStm &exp) override;
	void Visit(CWhileStm &exp) override;

	int GetResult();

private:
	int childResult;

	bool isChildResultInteger;

	bool wasError = false;
};

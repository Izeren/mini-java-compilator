#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "IVisitor.h"
#include "../shared_ptrs_nodes/Statements.h"
#include "../shared_ptrs_nodes/Expressions.h"
#include "../shared_ptrs_nodes/Classes.h"

class CCalculateVisitor : public IVisitor {
public:

	void Visit(CIdExp &exp) override;
	void Visit(CIdPtrExp &exp) override;
	void Visit(CNumExp &exp) override;
	void Visit(COpExp &exp) override;
	void Visit(CLogExp &exp) override;
	void Visit(CLogOpExp &exp) override;
	void Visit(CCompExp &exp) override;
	void Visit(CUnarMinusExp &exp) override;

	void Visit(CAssignStm &stm) override;
	void Visit(CAssignSubscriptStm &stm) override;
	void Visit(CCompoundStm &stm) override;
	void Visit(CPrintStm &stm) override;
	void Visit(CSimpleStm &stm) override;
	void Visit(CIfStm &stm) override;
	void Visit(CWhileStm &stm) override;

	void Visit(CType &stm) override;
	void Visit(CField &stm) override;
	void Visit(CFieldList &stm) override;
	void Visit(CArgument &stm) override;
	void Visit(CArgumentList &stm) override;
	void Visit(CMethod &stm) override;
	void Visit(CMethodList &stm) override;
	void Visit(CClass &stm) override;
	void Visit(CClassList &stm) override;
	void Visit(CMainMethod &stm) override;
	void Visit(CMainClass &stm) override;
	void Visit(CProgram &stm) override;

	int GetResult();

private:
	int childResult;

	bool isChildResultInteger;

	bool wasError = false;
};

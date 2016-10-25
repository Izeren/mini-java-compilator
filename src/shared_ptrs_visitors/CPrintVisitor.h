#pragma once

#include "IVisitor.h"
#include "../shared_ptrs_nodes/Statements.h"
#include "../shared_ptrs_nodes/Expressions.h"

#include <string>

class CPrintVisitor : public IVisitor {
public:

	CPrintVisitor();

	void Visit(CPrintStm &stm) override;
	void Visit(CCompoundStm &stm) override;
	void Visit(COpExp &exp) override;
	void Visit(CNumExp &exp) override;
	void Visit(CIdExp &exp) override;
	void Visit(CAssignStm &exp) override;
	void Visit(CSimpleStm &exp) override;
    
	std::string getDescription();

private:
	int lastVisited;
	std::string description;
};

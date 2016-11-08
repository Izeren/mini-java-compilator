#pragma once

#include "CType.h"
#include "Expressions.h"

class CArgument : public INode {
public:

	void Accept(IVisitor &visitor) override;
	CArgument();
	CArgument(CType *_type, CIdExp *_id);

	std::unique_ptr<CType> type;
	std::unique_ptr<CIdExp> id;

};
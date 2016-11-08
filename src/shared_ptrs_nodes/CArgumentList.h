#pragma once

#include "CArgument.h"

class CArgumentList : public INode {
public:

	void Accept(IVisitor &visitor) override;
	CArgumentList();
	CArgumentList(CArgument* _argument, CArgumentList* _argumentList);

	std::unique_ptr<CArgument> argument;
	std::unique_ptr<CArgumentList> argumentList;


};
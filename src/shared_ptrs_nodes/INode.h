#pragma once 

#include <memory>
#include <string>
#include "../shared_ptrs_visitors/IVisitor.h"

const std::string BAD_ID("Error_name");
class PositionInfo;

class INode {
public:
	virtual void Accept(IVisitor &) = 0;
	virtual ~INode() {}
};

class PositionedNode : public INode {
public:
	PositionInfo& position;
};
#pragma once 

#include <memory>
#include <string>
#include "../shared_ptrs_visitors/IVisitor.h"

const std::string BAD_ID("Error_name");

class PositionInfo
{
public:
	int firstLine;
	int lastLine;
	int firstColumn;
	int lastColumn;
	std::string GetStringPosition() const;
};

class INode {
public:
	virtual void Accept(IVisitor &) = 0;
	virtual ~INode() {}
};

class PositionedNode : public INode {
public:
	PositionInfo position;
	virtual void Accept(IVisitor &) = 0;
	virtual ~PositionedNode() {}
};
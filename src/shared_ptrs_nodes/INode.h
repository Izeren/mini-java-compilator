#pragma once 

#include <memory>
#include <string>
#include "../shared_ptrs_visitors/IVisitor.h"

const std::string BAD_ID("Error_name");

class INode {
public:
	virtual void Accept(IVisitor &) = 0;
	virtual ~INode() {}
};

class PositionedNode : public INode {
public:
	int firstLineNumber;
	int firstColumnNumber;
	int lastLineNumber;
	int lastColumnNumber;
	std::string GetStringLocation();
};
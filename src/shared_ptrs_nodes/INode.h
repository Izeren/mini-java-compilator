#pragma once 

#include <memory>
#include <string>
#include "../visitors/IVisitor.h"

const std::string BAD_ID("Error_name");

class INode {
public:
	virtual void Accept(IVisitor &) = 0;
	virtual ~INode() {}
};
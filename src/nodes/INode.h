#pragma once 

#include "../visitors/IVisitor.h"
#include "../visitors/IVisitorResult.h"

class INode {
public:
	virtual IVisitorResult* Accept(IVisitor *) = 0;

};
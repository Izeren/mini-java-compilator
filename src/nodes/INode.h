#pragma once 

#include "../visitors/IVisitor.h"

class INode {
private:
	virtual void Accept(IVisitor *) = 0

};
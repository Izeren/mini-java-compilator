#pragma once 

class INode {
private:
	virtual void Accept(IVisitor *) = 0

};
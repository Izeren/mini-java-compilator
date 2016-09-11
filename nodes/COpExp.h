#pragma once

class COpExp : public INode {
private:
	INode *leftOperand;
	INode *rightOperand;
	TOperation operaton;
};
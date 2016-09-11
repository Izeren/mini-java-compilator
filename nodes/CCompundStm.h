#pragma once

class CCompoundStm : public INode {
	INode *leftOperand;
	INode *rightOperand;
};
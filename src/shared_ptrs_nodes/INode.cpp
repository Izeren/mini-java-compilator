#include "INode.h"

std::string PositionedNode::GetStringLocation() {
	std::string result = "\"";
	result += std::to_string(firstLineNumber) + " ";
	result += std::to_string(firstColumnNumber) + " ";
	result += std::to_string(lastLineNumber) + " ";
	result += std::to_string(lastColumnNumber);
	result += "\"";
	return result;
}
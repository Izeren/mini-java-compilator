#include "PositionInfo.h"

//PositionInfo
//-------------------------------------------------------------------------------------------------

std::string PositionInfo::GetStringPosition() const {
	std::string result = "\"(";
	result += std::to_string(firstLine) + ",";
	result += std::to_string(firstColumn) + ") : (";
	result += std::to_string(lastLine) + ",";
	result += std::to_string(lastColumn);
	result += ")\"";
	return result;
}

PositionInfo PositionInfo::operator+(const PositionInfo &right) const {
    PositionInfo newPosition;
    newPosition.firstColumn = this->firstColumn;
    newPosition.firstLine = this->firstLine;
    newPosition.lastColumn = right.lastColumn;
    newPosition.lastLine = right.lastLine;
    return newPosition;
}


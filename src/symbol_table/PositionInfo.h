#pragma once

#include <string>

class PositionInfo
{
public:
	int firstLine;
	int lastLine;
	int firstColumn;
	int lastColumn;
	std::string GetStringPosition() const;
};
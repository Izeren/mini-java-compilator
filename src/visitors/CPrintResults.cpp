#include "CPrintResults.h"

CPrintResults::CPrintResults(std::string description) {
	this->description = description;
}

std::string CPrintResults::getDescription() {
	return description;
}

#include "IVisitorResult.h"
#include <string>

class CPrintResults : public IVisitorResult {

public:
	CPrintResults(std::string description = "");
	std::string getDescription();

private:
	std::string description;
};
#include "CArgumentList.h"


//cidexp:
//-------------------------------------------------------------------------------------------------

void CArgumentList::Accept(IVisitor &visitor) override
{
	visitor.visit(*this);
}

CArgumentList::CArgumentList()
{}

CArgumentList::CArgumentList(CArgument* _argument, CArgumentList* _argumentList)
{
	argument = std::unique_ptr<CArgument>(_statementList);
	argumentList = std::unique_ptr<CArgumentList>(_statementList);
}


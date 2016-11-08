#include "CMainMethod.h"


//cidexp:
//-------------------------------------------------------------------------------------------------

void CMainMethod::Accept(IVisitor &visitor) override
{
	visitor.visit(*this);
}

CMainMethod::CMainMethod()
{}

CMainMethod::CMainMethod(CCompoundStm* _statementList)
{
	statementList = _statementList;
}


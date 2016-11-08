#include "CMainClass.h"


//cidexp:
//-------------------------------------------------------------------------------------------------

void CMainClass::Accept(IVisitor &visitor) override
{
	visitor.visit(*this);
}

CMainClass::CMainClass()
{}

CMainClass::CMainClass(CIdExp* _id, CMainMethod* _mainMethod)
{
	id = std::unique_ptr<CIdExp>(_id);
	mainMethod = _mainMethod;
}


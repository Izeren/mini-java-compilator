#include "CProgram.h"


//cidexp:
//-------------------------------------------------------------------------------------------------

void CProgram::Accept(IVisitor &visitor) override
{
	visitor.visit(*this);
}

CProgram::CProgram()
{}

CProgram::CProgram(CMainClass* _mainClass, CClassList* _classList)
{
	mainClass = std::unique_ptr<CMainClass>(_mainClass);
	classList = std::unique_ptr<CClassList>(_classList);
}


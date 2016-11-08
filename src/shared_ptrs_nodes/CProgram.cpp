#include "CProgram.h"


//cidexp:
//-------------------------------------------------------------------------------------------------

void CProgram::Accept(IVisitor &visitor) override
{
	visitor.visit(*this);
}

CProgram::CProgram()
{}

CProgram::CProgram(CClass *_mainClass, CClassDeclarationList *_classList)
{
	mainClass = std::unique_ptr<CMainClass>(_mainClass);
	classList = _classList;
}


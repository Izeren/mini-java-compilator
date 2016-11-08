#include "CArgument.h"


//cidexp:
//-------------------------------------------------------------------------------------------------

void CArgument::Accept(IVisitor &visitor) override
{
	visitor.visit(*this);
}

CArgument::CArgument()
{}

CArgument::CArgument(CType *_type, CIdExp *_id)
{
	type = std::unique_ptr<CType>(_type);
	id = std::unique_ptr<CIdExp>(_id);
}


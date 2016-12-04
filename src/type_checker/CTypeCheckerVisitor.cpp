#include "CTypeCheckerCTypeCheckerVisitor::Visitor.h"

CTypeCheckerCTypeCheckerVisitor::Visitor::CTypeCheckerCTypeCheckerVisitor::Visitor(std::shared_ptr<SymbolTable> table) 
{
	this->table = table;
}


//Expressions visit methods
//---------------------------------------------------------------------------------------
void CTypeCheckerVisitor::Visit( CIdExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CIdPtrExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CNumExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( COpExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CLogExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CLogOpExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CCompExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CUnarMinusExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CGetLengthExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CGetFieldExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CCallMethodExp &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CExpList &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CNegativeExpression &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CArrayExpression &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CThisExpression &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CByIndexExpression &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CNewIdentifier &exp ) 
{

}
//Statements visit methods
//---------------------------------------------------------------------------------------
void CTypeCheckerVisitor::Visit( CAssignStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CAssignSubscriptStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CCompoundStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CPrintStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CSimpleStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CIfStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CWhileStm &stm ) 
{

}
//Classes visit methods
//---------------------------------------------------------------------------------------
void CTypeCheckerVisitor::Visit( CType &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CField &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CFieldList &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CArgument &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CArgumentList &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CMethod &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CMethodList &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CClass &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CClassList &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CMainMethod &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CMainClass &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CProgram &stm ) 
{

}

std::shared_ptr<SymbolTable> GetSymbolTable() const
{

}
std::vector<CError> GetErrors()
{
	
}
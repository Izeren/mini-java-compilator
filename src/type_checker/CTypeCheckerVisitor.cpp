#include "CTypeCheckerVisitor.h"
#include "../symbol_table/SymbolInfo.h"
#include "../nodes/statements/CPrintStm.h"
#include "../nodes/statements/CAssignStm.h"

CTypeCheckerVisitor::CTypeCheckerVisitor(std::shared_ptr<SymbolTable> table, IExpression &lastCalculated,
										 CType &lastCalculatedType)
		: lastCalculated(lastCalculated), lastCalculatedType(lastCalculatedType), table(table) {
}


//Expressions visit methods
//---------------------------------------------------------------------------------------
void CTypeCheckerVisitor::Visit( CIdExp &exp ) 
{
	lastCalculated = exp;
}
void CTypeCheckerVisitor::Visit( CIdPtrExp &exp ) 
{
	lastCalculated = exp;
}
void CTypeCheckerVisitor::Visit( CNumExp &exp ) 
{
	lastCalculated = exp;
}
void CTypeCheckerVisitor::Visit( COpExp &exp ) 
{
	if( exp.leftOperand ){
		exp.leftOperand->Accept( *this );
	}
    if( !lastCalculatedType.isPrimitive ) {
		errors.push_back( CError("Left operand has non-primitive type is not defined", exp.position) );
	}
	auto leftType = lastCalculatedType;
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
	if( !lastCalculatedType.isPrimitive ) {
		errors.push_back( CError("Right operand has non-primitive type is not defined", exp.position) );
	}
	if( leftType.type != lastCalculatedType.type ) {
		errors.push_back( CError( "Operands have different primitive types", exp.position ) );
	}

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
	if ( exp.lengthExpression ) {
		exp.lengthExpression->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::INT ) {
		errors.push_back( CError( "Length of the array must be integer", exp.position ) );
	}
}
void CTypeCheckerVisitor::Visit( CThisExpression &exp ) 
{

}
void CTypeCheckerVisitor::Visit( CByIndexExpression &exp ) 
{
	if( exp.arrayExpression ) {
		exp.arrayExpression->Accept( *this );
	}
	if( exp.indexExpression ) {
		exp.indexExpression->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::INT ) {
		errors.push_back( CError( "The index of the array must be integer", exp.position ) );
	}
}
void CTypeCheckerVisitor::Visit( CNewIdentifier &exp ) 
{

}
//Statements visit methods
//---------------------------------------------------------------------------------------
void CTypeCheckerVisitor::Visit( CAssignStm &stm ) 
{
	if( stm.leftExpression ) {
		stm.leftExpression->Accept( *this );
	}
	auto leftType = lastCalculatedType.type;
	if( stm.rightExpression ) {
		stm.rightExpression->Accept( *this );
	}
	if( leftType != lastCalculatedType.type ) {
		errors.push_back( CError( "The type of the assigned value must be the same as the type of variable", stm.position) );
	}
}
void CTypeCheckerVisitor::Visit( CAssignSubscriptStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CCompoundStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CPrintStm &stm ) 
{
    if( stm.expression ) {
        stm.expression->Accept( *this );
    }
    if( lastCalculatedType.type != enums::TPrimitiveType::INT ) {
        errors.push_back( CError( "The type of the expression to be printed should be INT", stm.position ) );
    }
}
void CTypeCheckerVisitor::Visit( CSimpleStm &stm ) 
{

}
void CTypeCheckerVisitor::Visit( CIfStm &stm ) 
{
	if( stm.conditionExpression ) {
		stm.conditionExpression->Accept( *this );
		if( lastCalculatedType.type != enums::TPrimitiveType::BOOLEAN ) {
			errors.push_back( CError( "The expression in If statement must be boolean", stm.position ) );
		}
	}
	if( stm.positiveStatement ) {
		stm.positiveStatement->Accept( *this );
	}
	if( stm.negativeStatement ) {
		stm.negativeStatement->Accept( *this );
	}
}
void CTypeCheckerVisitor::Visit( CWhileStm &stm ) 
{
	if( stm.conditionExpression ) {
		stm.conditionExpression->Accept( *this );
		if( lastCalculatedType.type != enums::TPrimitiveType::BOOLEAN ) {
			errors.push_back( CError( "The expression in While statement must be boolean", stm.position ) );
		}
	}
	if( stm.statement ) {
		stm.statement->Accept( *this );
	}
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
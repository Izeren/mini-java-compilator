#include "CTypeCheckerVisitor.h"
#include "../symbol_table/SymbolInfo.h"
#include "../nodes/statements/CPrintStm.h"
#include "../nodes/statements/CAssignStm.h"

CTypeCheckerVisitor::CTypeCheckerVisitor(std::shared_ptr<SymbolTable> table, IExpression &lastCalculated,
										 TypeInfo& lastCalculatedType)
		: lastCalculated(lastCalculated), lastCalculatedType(lastCalculatedType), table(table) {
}


//Expressions visit methods
//---------------------------------------------------------------------------------------
void CTypeCheckerVisitor::Visit( CIdExp &exp ) 
{
}
void CTypeCheckerVisitor::Visit( CIdPtrExp &exp ) 
{
	lastCalculatedType = TypeInfo( enums::TPrimitiveType::INT_ARRAY );
}
void CTypeCheckerVisitor::Visit( CNumExp &exp ) 
{
	lastCalculatedType = TypeInfo( enums::TPrimitiveType::INT );
}
void CTypeCheckerVisitor::Visit( COpExp &exp ) 
{
	if( exp.leftOperand ){
		exp.leftOperand->Accept( *this );
	}
    if( lastCalculatedType.type != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::INT ), lastCalculatedType );
		errors.push_back( CError ( errorMessage, exp.position ) );
		lastCalculatedType = TypeInfo(enums::TPrimitiveType::ERROR_TYPE);
		return;
	}
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::INT ), lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position) );
        lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
		return;
	}
	lastCalculatedType = TypeInfo( enums::TPrimitiveType::INT );
}

void CTypeCheckerVisitor::Visit( CLogExp &exp ) 
{
	lastCalculatedType = TypeInfo( enums::TPrimitiveType::BOOLEAN );
}

void CTypeCheckerVisitor::Visit( CLogOpExp &exp ) 
{
	if( exp.leftOperand ) {
		exp.leftOperand->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::BOOLEAN ) {
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::BOOLEAN ), lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
		return;
	}
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::BOOLEAN ) {
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::BOOLEAN ), lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position));
		lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
		return;
	}
	lastCalculatedType = TypeInfo( enums::TPrimitiveType::BOOLEAN );
}

void CTypeCheckerVisitor::Visit( CCompExp &exp ) 
{
	if( exp.leftOperand ) {
		exp.leftOperand->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::INT ), lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
		return;
	}
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::INT ), lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
		return;
	}
	lastCalculatedType = TypeInfo( enums::TPrimitiveType::BOOLEAN );
}

void CTypeCheckerVisitor::Visit( CUnarMinusExp &exp ) 
{
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::INT ) {
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::INT ), lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
		return;
	}
	lastCalculatedType = TypeInfo( enums::TPrimitiveType::INT );
}
void CTypeCheckerVisitor::Visit( CGetLengthExp &exp ) 
{
	if( exp.array ) {
		exp.array->Accept( *this );
	}
	if( lastCalculatedType.type != enums::TPrimitiveType::INT_ARRAY ) {
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::INT_ARRAY ), lastCalculatedType );
		errors.push_back( CError( errorMessage, exp.position ) );
		lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
		return;
	}
	lastCalculatedType = TypeInfo( enums::TPrimitiveType::INT );
}

void CTypeCheckerVisitor::Visit( CGetFieldExp &exp ) 
{
	if( exp.classOwner && exp.field ) {
		std::string ownerName = exp.classOwner->id->name;
		std::string fieldName = exp.field->id->name;
		auto ownerIterator = table->classes.find(ownerName);
		if( ownerIterator == table->classes.end() ) {
			auto errorMessage = CError::GetUndeclaredErrorMessage( ownerName );
			errors.push_back( CError( errorMessage, exp.position ) );
			lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
			return;
		}
        auto ownerInfo = table->classes[ownerName];
        auto variablesInfo = ownerInfo->fields;
        auto fieldIterator = variablesInfo->variables.find(fieldName);
        if( fieldIterator == variablesInfo->variables.end() ) {
            auto errorMessage = CError::GetHasNoMemberErrorMessage( ownerName, fieldName );
            errors.push_back( CError( errorMessage, exp.position ) );
            lastCalculatedType = TypeInfo( enums::TPrimitiveType::ERROR_TYPE );
            return;
        }

		auto fieldInfo = variablesInfo->variables[fieldName];
		lastCalculatedType = *(fieldInfo->type);
	} else {
		errors.push_back( CError( CError::AST_ERROR, exp.position ) );
	}
}

void CTypeCheckerVisitor::Visit( CCallMethodExp &exp ) 
{
	if( exp.args && exp.classOwner && exp.methodName) {

	} else {
		errors.push_back( CError( CError::AST_ERROR, exp.position ) );
	}
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
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::INT ), lastCalculatedType.type );
		errors.push_back( CError( errorMessage, exp.position ) );
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
		auto errorMessage = CError::GetTypeErrorMessage( TypeInfo( enums::TPrimitiveType::INT ), lastCalculatedType.type );
		errors.push_back( CError( errorMessage, exp.position ) );
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
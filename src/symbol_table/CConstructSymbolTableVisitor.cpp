#include "CConstructSymbolTableVisitor.h"
#include "../Utils.h"
#include <iostream>

CConstructSymbolTableVisitor::CConstructSymbolTableVisitor()
{
	info = std::shared_ptr<FullInfo>( new FullInfo() );
	table = std::shared_ptr<SymbolTable>( new SymbolTable() );
}



//Expressions:
//-------------------------------------------------------------------------------------------------

void CConstructSymbolTableVisitor::Visit( CIdExp &exp )
{
	info->iName = exp.name;
}

void CConstructSymbolTableVisitor::Visit( CIdPtrExp &exp )
{
	info->iName = exp.name;
}

void CConstructSymbolTableVisitor::Visit( CNumExp &exp )
{}

void CConstructSymbolTableVisitor::Visit( COpExp &exp )
{
	if( exp.leftOperand ) {
		exp.leftOperand->Accept( *this );
	}
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CLogExp &exp )
{}

void CConstructSymbolTableVisitor::Visit( CLogOpExp &exp )
{
	if( exp.leftOperand ) {
		exp.leftOperand->Accept( *this );
	}
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CCompExp &exp )
{
	if( exp.leftOperand ) {
		exp.leftOperand->Accept( *this );
	}
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CUnarMinusExp &exp )
{
	if( exp.rightOperand ) {
		exp.rightOperand->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CGetLengthExp &exp )
{
	if( exp.array ) {
		exp.array->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CGetFieldExp &exp )
{
	if( exp.classOwner ) {
		exp.classOwner->Accept( *this );
	}
	if( exp.field ) {
		exp.field->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CCallMethodExp &exp )
{
	if( exp.classOwner ) {
		exp.classOwner->Accept( *this );
	}
	if( exp.methodName ) {
		exp.methodName->Accept( *this );
	}
	if( exp.args ) {
		exp.args->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CExpList &stm )
{
	if( stm.exps.size() ) {
		for( int index = 0; index < stm.exps.size(); ++index ) {
			if( stm.exps[index].get() ) {
				stm.exps[index].get()->Accept( *this );
			}
		}
	}
}

void CConstructSymbolTableVisitor::Visit( CNegativeExpression &exp )
{
	if( exp.expression ) {
		exp.expression->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CArrayExpression &exp )
{
	if( exp.lengthExpression ) {
		exp.lengthExpression->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CThisExpression &exp )
{}

void CConstructSymbolTableVisitor::Visit( CByIndexExpression &exp )
{
	if( exp.arrayExpression ) {
		exp.arrayExpression->Accept( *this );
	}
	if( exp.indexExpression ) {
		exp.indexExpression->Accept( *this );
	}
}



//Statements:
//-------------------------------------------------------------------------------------------------

void CConstructSymbolTableVisitor::Visit( CAssignStm &stm )
{
	if( stm.leftExpression ) {
		stm.leftExpression->Accept( *this );
	}
	if( stm.rightExpression ) {
		stm.rightExpression->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CAssignSubscriptStm &stm )
{
	if( stm.idExpression ) {
		stm.idExpression->Accept( *this );
	}
	if( stm.offset ) {
		stm.offset->Accept( *this );
	}
	if( stm.valueExpression ) {
		stm.valueExpression->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CCompoundStm &stm )
{
	if( stm.leftStatement ) {
		stm.leftStatement->Accept( *this );
	}
	if( stm.rightStatement ) {
		stm.rightStatement->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CPrintStm &stm )
{
	if( stm.expression ) {
		stm.expression->Accept( *this );
	}

}

void CConstructSymbolTableVisitor::Visit( CSimpleStm &stm )
{
	if( stm.statement ) {
		stm.statement->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CIfStm &stm )
{
	if( stm.conditionExpression ) {
		stm.conditionExpression->Accept( *this );
	}
	if( stm.positiveStatement ) {
	}
	if( stm.negativeStatement ) {
	}
}

void CConstructSymbolTableVisitor::Visit( CWhileStm &stm )
{
	if( stm.conditionExpression ) {
		stm.conditionExpression->Accept( *this );
	}
	if( stm.statement ) {
		stm.statement->Accept( *this );
	}
}



//Classes:
//-------------------------------------------------------------------------------------------------

void CConstructSymbolTableVisitor::Visit( CType &stm )
{
    std::cout << "type\n";
	if( stm.isPrimitive ) {
		info->iType = std::shared_ptr<TypeInfo>( new TypeInfo( stm.type ) );
	} else {
		std::string curName = info->iName;
		info->iName = "";
		stm.name->Accept( *this );
		info->iType = std::shared_ptr<TypeInfo>( new TypeInfo( info->iName ) );
		info->iName = curName;
	}
}

void CConstructSymbolTableVisitor::Visit( CField &stm )
{
	std::cout << "field\n";
	info->iType = nullptr;
	if( stm.type ) {
		stm.type->Accept( *this );
	}
	info->iName = "";
	if( stm.id ) {
		stm.id->Accept( *this );
	}
	info->iVariable = std::shared_ptr<VariableInfo>( new VariableInfo( info->iName, info->iType ) );
}

void CConstructSymbolTableVisitor::Visit( CFieldList &stm )
{
	std::cout << "fieldlist\n";
	if( stm.fields.size() ) {
		for( int index = 0; index < stm.fields.size(); ++index ) {
			if( stm.fields[index].get() ) {
				info->iVariable = nullptr;
				stm.fields[index].get()->Accept( *this );
				info->iClass->AddField( info->iVariable );
			}
		}
	}
}

void CConstructSymbolTableVisitor::Visit( CArgument &stm )
{
	std::cout << "arg\n";
	info->iType = nullptr;
	if( stm.type ) {
		stm.type->Accept( *this );
	}
	info->iName = "";
	if( stm.id ) {
		stm.id->Accept( *this );
	}
	info->iVariable = std::shared_ptr<VariableInfo>( new VariableInfo( info->iName, info->iType ) );
}

void CConstructSymbolTableVisitor::Visit( CArgumentList &stm )
{
	std::cout << "arglist\n";
	if( stm.arguments.size() ) {
		for( int index = 0; index < stm.arguments.size(); ++index ) {
			if( stm.arguments[index].get() ) {
				info->iVariable = nullptr;
				stm.arguments[index].get()->Accept( *this );
				info->iMethod->AddVariable( info->iVariable );
			}
		}
	}
}

void CConstructSymbolTableVisitor::Visit( CMethod &stm )
{
	std::cout << "method\n";
	info->iName = "";
	stm.name->Accept( *this );

	info->iType = nullptr;
	stm.returnType->Accept( *this );
    
	info->iMethod = std::shared_ptr<MethodInfo>( new MethodInfo( info->iName, stm.isPublic, info->iType ) );
    
	if( stm.arguments ) {
		stm.arguments->Accept( *this );
	}
	if( stm.vars ) {
		stm.vars->Accept( *this );
	}
	if( stm.statements ) {
		stm.statements->Accept( *this );
	}
	if( stm.returnExp ) {
		stm.returnExp->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CMethodList &stm )
{
	std::cout << "methodlist\n";
	if( stm.methods.size() ) {
		for( int index = 0; index < stm.methods.size(); ++index ) {
			if( stm.methods[index].get() ) {
				info->iMethod = nullptr;
				stm.methods[index].get()->Accept( *this );
				info->iClass->AddMethod( info->iMethod );
			}
		}
	}
}

void CConstructSymbolTableVisitor::Visit( CClass &stm )
{
	std::cout << "class\n";
	info->iName = "";
	if( stm.id ) {
		stm.id->Accept( *this );
	}
	info->iClass = std::shared_ptr<ClassInfo>( new ClassInfo( info->iName ) );

	if( stm.parentClass ) {
		info->iName = "";
		stm.parentClass->Accept( *this );
		info->iClass->baseClass = info->iName;
	}

	if( stm.fields ) {
		stm.fields->Accept( *this );
	}
	if( stm.methods ) {
		stm.methods->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CClassList &stm )
{
	std::cout << "classlist\n";
	if( stm.classes.size() ) {
		for( int index = 0; index < stm.classes.size(); ++index ) {
			if( stm.classes[index].get() ) {
				info->iClass = nullptr;
				stm.classes[index].get()->Accept( *this );
				table->AddClass( info->iClass );
			}
		}
	}
}

void CConstructSymbolTableVisitor::Visit( CMainMethod &stm )
{
	std::cout << "mainmethod\n";

	// TODO: should be corrected?
	//info->iType = "";
	//if( stm.returnType ) {
	//	stm.returnType->Accept( *this );
	//}
	//info->iMethod->returnType = info->iType;

	info->iMethod = std::shared_ptr<MethodInfo>( new MethodInfo( MAIN_NAME, true, nullptr ) );

	info->iType = std::shared_ptr<TypeInfo>( new TypeInfo( enums::TPrimitiveType::STRING_ARRAY ) );
    
	info->iName = "";
	if( stm.args ) {
		stm.args->Accept( *this );
	}
	info->iVariable = std::shared_ptr<VariableInfo>( new VariableInfo( info->iName, info->iType ) );
	info->iMethod->AddVariable( info->iVariable );

	if( stm.vars ) {
		stm.vars->Accept( *this );
	}
	if( stm.statements ) {
		stm.statements->Accept( *this );
	}
}

void CConstructSymbolTableVisitor::Visit( CMainClass &stm )
{
	std::cout << "mainclass\n";
	info->iName = "";
	if( stm.id ) {
		stm.id->Accept( *this );
	}
	info->iClass = std::shared_ptr<ClassInfo>( new ClassInfo( info->iName ) );

	info->iMethod = nullptr;
	if( stm.mainMethod ) {
		stm.mainMethod->Accept( *this );
	}
	info->iClass->AddMethod( info->iMethod );
}

void CConstructSymbolTableVisitor::Visit( CProgram &stm )
{
	std::cout << "program\n";
	if( stm.classList ) {
		stm.classList->Accept( *this );
	}

	info->iClass = nullptr;
	if( stm.mainClass ) {
		stm.mainClass->Accept( *this );
	}
	table->AddClass( info->iClass );
}


std::shared_ptr<SymbolTable> CConstructSymbolTableVisitor::GetSymbolTable()
{
	return table;
}
#pragma once

#include "../shared_ptrs_visitors/IVisitor.h"
#include "../shared_ptrs_nodes/Statements.h"
#include "../shared_ptrs_nodes/Expressions.h"
#include "../shared_ptrs_nodes/Classes.h"
#include "../symbol_table/SymbolInfo.h"

#include <string>
#include <utility>

class CTypeCheckerVisitor : public IVisitor
{
public:

	CTypeCheckerVisitor( std::shared_ptr<SymbolTable> table );

	void Visit( CIdExp &exp ) override;
	void Visit( CIdPtrExp &exp ) override;
	void Visit( CNumExp &exp ) override;
	void Visit( COpExp &exp ) override;
	void Visit( CLogExp &exp ) override;
	void Visit( CLogOpExp &exp ) override;
	void Visit( CCompExp &exp ) override;
	void Visit( CUnarMinusExp &exp ) override;
	void Visit( CGetLengthExp &exp ) override;
	void Visit( CCallMethodExp &exp ) override;
	void Visit( CExpList &exp ) override;
	void Visit( CNegativeExpression &exp ) override;
	void Visit( CNewArrayExpression &exp ) override;
	void Visit( CByIndexExpression &exp ) override;
	void Visit( CNewIdentifier &exp ) override;
	void Visit(CThisExpression &exp) override;
	void Visit(CGetFieldByThisExpression &exp) override;

	void Visit( CAssignStm &stm ) override;
	void Visit( CAssignSubscriptStm &stm ) override;
	void Visit( CCompoundStm &stm ) override;
	void Visit( CPrintStm &stm ) override;
	void Visit( CIfStm &stm ) override;
	void Visit( CWhileStm &stm ) override;

	void Visit( CType &stm ) override;
	void Visit( CField &stm ) override;
	void Visit( CFieldList &stm ) override;
	void Visit( CArgument &stm ) override;
	void Visit( CArgumentList &stm ) override;
	void Visit( CMethod &stm ) override;
	void Visit( CMethodList &stm ) override;
	void Visit( CClass &stm ) override;
	void Visit( CClassList &stm ) override;
	void Visit( CMainMethod &stm ) override;
	void Visit( CMainClass &stm ) override;
	void Visit( CProgram &stm ) override;

	std::vector<CError> GetErrors();

private:
	std::shared_ptr<SymbolTable> table;
	std::vector<CError> errors;
    TypeInfo lastCalculatedType;
    std::shared_ptr<ClassInfo> currentClass;
    std::shared_ptr<MethodInfo> currentMethod;

	bool shouldSearchIdInFields = false;

    //bool -- isLocalVariable
    std::pair<VariableInfo*, bool> getVariableInfo(CIdExp& exp);

	bool checkVariableVisibility( const std::string& variableName, std::shared_ptr<ClassInfo> classInfo,
std::shared_ptr<MethodInfo> methodInfo );
	bool checkMethodVisibility( const std::string& methodName, std::shared_ptr<ClassInfo> clazz, bool isThis );
	bool checkTypeExisting(const CType &className);
	bool checkCyclicInheritance( std::shared_ptr<ClassInfo> startClass, std::shared_ptr<ClassInfo> currentClass );
	std::vector<std::unordered_map<std::string, std::shared_ptr<VariableInfo>>*> getSuperFields();
};

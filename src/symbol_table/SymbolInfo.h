#pragma once

#include <string>
#include <unordered_map>
#include <memory> 
#include <fstream>
#include "../Utils.h"
#include "../shared_ptrs_nodes/Classes.h"
#include "PositionInfo.h"

class TypeInfo
{
public:
	TypeInfo( enums::TPrimitiveType _type );
	TypeInfo( const std::string& _className );

	void Print( std::ofstream& out );

	bool isPrimitive;
	enums::TPrimitiveType type;
	std::string className;
};
bool operator==(const TypeInfo& left, const TypeInfo& right);
bool operator!=(const TypeInfo& left, const TypeInfo& right);

class VariableInfo
{
public:
	VariableInfo( const std::string& _name, std::shared_ptr<TypeInfo> _type );

	void Print( std::ofstream& out );

	std::string name;
	std::shared_ptr<TypeInfo> type;
};

class VariablesInfo
{
public:
	VariablesInfo();

	void Print( std::ofstream& out );

	void AddVariable( std::shared_ptr<VariableInfo> variableInfo );

	std::unordered_map<std::string, std::shared_ptr<VariableInfo>> variables;

    std::vector<std::string> variableNames;
};

class MethodInfo
{
public:
	MethodInfo( const std::string& _name, bool _isPublic, std::shared_ptr<TypeInfo> _returnType );

	void Print( std::ofstream& out );

	std::string name;	
	bool isPublic;
	std::shared_ptr<TypeInfo> returnType;
	std::shared_ptr<VariablesInfo> arguments;
	std::shared_ptr<VariablesInfo> fields;
};

class ClassInfo 
{
public:
	ClassInfo( const std::string& _name);

	void AddMethod( std::shared_ptr<MethodInfo> methodInfo );

	void Print( std::ofstream& out );

	std::string name;
	std::shared_ptr<VariablesInfo> fields;
	std::unordered_map<std::string, std::shared_ptr<MethodInfo>> methods;
	std::string baseClass;
};

class FullInfo
{
public:
	std::shared_ptr<ClassInfo> iClass;
	std::shared_ptr<MethodInfo> iMethod;
	std::shared_ptr<VariablesInfo> iVariables;
	std::shared_ptr<VariableInfo> iVariable;
	std::shared_ptr<TypeInfo> iType;
	std::string iName;
};

class SymbolTable
{
public:
	void AddClass( std::shared_ptr<ClassInfo> classInfo );

	void Print( std::ofstream& out );

	std::unordered_map<std::string, std::shared_ptr<ClassInfo>> classes;
};

class CError
{
public:
	CError( const std::string& _message, const PositionInfo &position);

	CError( const std::string& _message);


	std::string& GetMessage();
	PositionInfo GetPosition();

	static const std::string FUNCTION_REDEFINITION;
	static const std::string VARIABLE_REDEFINITION;
	static const std::string CLASS_REDEFINITION;
    static const std::string AST_ERROR;
	static const std::string IS_NOT_CALLABLE;

	static std::string GetTypeErrorMessage( const TypeInfo& expected, const TypeInfo& got );
    static std::string GetNumberOfArgsMessage( unsigned long expected, unsigned long got );
    static std::string GetUndeclaredErrorMessage( const std::string& name );
	static std::string GetHasNoMemberErrorMessage( const std::string& className, const std::string& fieldName );

private:
	std::string message;
	PositionInfo position;
};
#pragma once

#include <string>
#include <unordered_map>
#include <memory> 
#include <fstream>
#include "../Utils.h"
#include "../shared_ptrs_nodes/Classes.h"


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
};

class MethodInfo
{
public:
	MethodInfo( const std::string& _name, bool _isPublic, std::shared_ptr<TypeInfo> _returnType );

	void Print( std::ofstream& out );

	std::string name;	
	bool isPublic;
	std::shared_ptr<TypeInfo> returnType;
	std::shared_ptr<VariablesInfo> variables;
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
	CError( const std::string& _message );

	std::string& GetMessage();

	static const std::string REDEFINITION_FUNCTION;

private:
	std::string message;
};
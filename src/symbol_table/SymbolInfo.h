#pragma once

#include <string>
#include <unordered_map>

//class Info
//{
//public:
//	Info( std::string& _name );
//	std::string name;
//};

//class TypeInfo
//{
//public:
//	std::string name;
//};

class PrimitiveTypeInfo
{
public:
	std::string name;
};

class VariableInfo
{
public:
	VariableInfo( const std::string& _name, const std::string& _type );

	std::string name;
	std::string type;
};

class MethodInfo
{
public:
	MethodInfo( const std::string& _name );

	void AddVariable( std::shared_ptr<VariableInfo> variableInfo );

	std::string name;
	std::unordered_map<std::string, std::shared_ptr<VariableInfo>> variables;
	std::string returnType;
	bool isPublic;
};

class ClassInfo //: TypeInfo
{
public:
	ClassInfo( const std::string& _name);

	void AddField( std::shared_ptr<VariableInfo> fieldInfo );
	void AddMethod( std::shared_ptr<MethodInfo> methodInfo );

	std::string name;
	std::unordered_map<std::string, std::shared_ptr<VariableInfo>> fields;
	std::unordered_map<std::string, std::shared_ptr<MethodInfo>> methods;
	std::string baseClass;
};

class FullInfo
{
public:
	std::shared_ptr<ClassInfo> iClass;
	std::shared_ptr<MethodInfo> iMethod;
	std::shared_ptr<VariableInfo> iVariable;
	std::string iName;
	std::string iType;
};

class SymbolTable
{
public:
	void AddClass( std::shared_ptr<ClassInfo> classInfo );

	std::unordered_map<std::string, std::shared_ptr<ClassInfo>> classes;
};